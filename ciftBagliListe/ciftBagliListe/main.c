//  main.c
//  ciftBagliListe
//  Created by Uğur Burak Berber on 20.12.2023.


// int main(int argc, const char * argv[])

#include <stdio.h>
#include <stdlib.h>

struct dugum {
    int data;
    struct dugum* sonraki;
};

void basiSil(struct dugum** head_ref) {
    if (*head_ref == NULL) {
        printf("Liste zaten bos.\n");
        return;
    }

    struct dugum* temp = *head_ref;
    *head_ref = temp->sonraki;
    free(temp);
}

void sonuSil(struct dugum** head_ref) {
    if (*head_ref == NULL) {
        printf("Liste zaten bos.\n");
        return;
    }

    if ((*head_ref)->sonraki == NULL) {
        free(*head_ref);
        *head_ref = NULL;
        return;
    }

    struct dugum* son = *head_ref;
    struct dugum* onceki = NULL;

    while (son->sonraki != NULL) {
        onceki = son;
        son = son->sonraki;
    }

    onceki->sonraki = NULL;
    free(son);
}

void aradanSil(struct dugum** head_ref, int pozisyon) {
    if (*head_ref == NULL) {
        printf("Liste zaten bos.\n");
        return;
    }

    struct dugum* temp = *head_ref;

    if (pozisyon == 0) {
        *head_ref = temp->sonraki;
        free(temp);
        return;
    }

    for (int i = 0; temp != NULL && i < pozisyon - 1; i++) {
        temp = temp->sonraki;
    }

    if (temp == NULL || temp->sonraki == NULL) {
        printf("Gecersiz pozisyon.\n");
        return;
    }

    struct dugum* silinecek = temp->sonraki;
    temp->sonraki = silinecek->sonraki;
    free(silinecek);
}

void basaEkle(struct dugum** head_ref, int yeni_veri) {
    struct dugum* yeni_dugum = (struct dugum*)malloc(sizeof(struct dugum));
    yeni_dugum->data = yeni_veri;
    yeni_dugum->sonraki = *head_ref;
    *head_ref = yeni_dugum;
}

void sonaEkle(struct dugum** head_ref, int yeni_veri) {
    struct dugum* yeni_dugum = (struct dugum*)malloc(sizeof(struct dugum));
    struct dugum* son = *head_ref;

    yeni_dugum->data = yeni_veri;
    yeni_dugum->sonraki = NULL;

    if (*head_ref == NULL) {
        *head_ref = yeni_dugum;
        return;
    }

    while (son->sonraki != NULL) {
        son = son->sonraki;
    }

    son->sonraki = yeni_dugum;
}

struct dugum* ara(struct dugum* head, int aranan) {
    while (head != NULL) {
        if (head->data == aranan) {
            return head;
        }
        head = head->sonraki;
    }
    return NULL;
}

void listeYazdir(struct dugum* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->sonraki;
    }
}

int main() {
    struct dugum* head = NULL;
    int sayi, devam, secim, pozisyon, aranan;
    struct dugum* bulunan;

    do {
        printf("Bir sayi girin: ");
        scanf("%d", &sayi);

        printf("Nereye eklemek/silmek/aramak istiyorsunuz? (1: Başa ekle, 2: Sona ekle, 3: Baştan sil, 4: Sondan sil, 5: Belirli pozisyondan sil, 6: Arama yap): ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                basaEkle(&head, sayi);
                break;
            case 2:
                sonaEkle(&head, sayi);
                break;
            case 3:
                basiSil(&head);
                break;
            case 4:
                sonuSil(&head);
                break;
            case 5:
                printf("Silinecek pozisyonu girin: ");
                scanf("%d", &pozisyon);
                aradanSil(&head, pozisyon);
                break;
            case 6:
                printf("Aranacak sayiyi girin: ");
                scanf("%d", &aranan);
                bulunan = ara(head, aranan);
                if (bulunan != NULL) {
                    printf("%d bulundu.\n", aranan);
                } else {
                    printf("%d bulunamadi.\n", aranan);
                }
                break;
            default:
                printf("Geçersiz seçim!\n");
                break;
        }

        printf("Devam etmek istiyor musunuz? (1: Evet, 0: Hayır): ");
        scanf("%d", &devam);
    } while (devam != 0);

    printf("Girilen sayilar: ");
    listeYazdir(head);

    return 0;
}
