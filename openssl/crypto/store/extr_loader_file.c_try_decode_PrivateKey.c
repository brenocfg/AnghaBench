#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UI_METHOD ;
struct TYPE_4__ {int pkey_flags; int /*<<< orphan*/  pkey_id; } ;
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  int /*<<< orphan*/  OSSL_STORE_INFO ;
typedef  TYPE_1__ EVP_PKEY_ASN1_METHOD ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int ASN1_PKEY_ALIAS ; 
 int /*<<< orphan*/ * EVP_PKCS82PKEY (int /*<<< orphan*/ *) ; 
 TYPE_1__* EVP_PKEY_asn1_find_str (int /*<<< orphan*/ *,char const*,int) ; 
 TYPE_1__* EVP_PKEY_asn1_get0 (int) ; 
 int EVP_PKEY_asn1_get_count () ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OSSL_STORE_INFO_new_PKEY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEM_STRING_PKCS8INF ; 
 int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_PKCS8_PRIV_KEY_INFO (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 int /*<<< orphan*/ * d2i_PrivateKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 int pem_check_suffix (char const*,char*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OSSL_STORE_INFO *try_decode_PrivateKey(const char *pem_name,
                                              const char *pem_header,
                                              const unsigned char *blob,
                                              size_t len, void **pctx,
                                              int *matchcount,
                                              const UI_METHOD *ui_method,
                                              void *ui_data)
{
    OSSL_STORE_INFO *store_info = NULL;
    EVP_PKEY *pkey = NULL;
    const EVP_PKEY_ASN1_METHOD *ameth = NULL;

    if (pem_name != NULL) {
        if (strcmp(pem_name, PEM_STRING_PKCS8INF) == 0) {
            PKCS8_PRIV_KEY_INFO *p8inf =
                d2i_PKCS8_PRIV_KEY_INFO(NULL, &blob, len);

            *matchcount = 1;
            if (p8inf != NULL)
                pkey = EVP_PKCS82PKEY(p8inf);
            PKCS8_PRIV_KEY_INFO_free(p8inf);
        } else {
            int slen;

            if ((slen = pem_check_suffix(pem_name, "PRIVATE KEY")) > 0
                && (ameth = EVP_PKEY_asn1_find_str(NULL, pem_name,
                                                   slen)) != NULL) {
                *matchcount = 1;
                pkey = d2i_PrivateKey(ameth->pkey_id, NULL, &blob, len);
            }
        }
    } else {
        int i;

        for (i = 0; i < EVP_PKEY_asn1_get_count(); i++) {
            EVP_PKEY *tmp_pkey = NULL;
            const unsigned char *tmp_blob = blob;

            ameth = EVP_PKEY_asn1_get0(i);
            if (ameth->pkey_flags & ASN1_PKEY_ALIAS)
                continue;

            tmp_pkey = d2i_PrivateKey(ameth->pkey_id, NULL, &tmp_blob, len);
            if (tmp_pkey != NULL) {
                if (pkey != NULL)
                    EVP_PKEY_free(tmp_pkey);
                else
                    pkey = tmp_pkey;
                (*matchcount)++;
            }
        }

        if (*matchcount > 1) {
            EVP_PKEY_free(pkey);
            pkey = NULL;
        }
    }
    if (pkey == NULL)
        /* No match */
        return NULL;

    store_info = OSSL_STORE_INFO_new_PKEY(pkey);
    if (store_info == NULL)
        EVP_PKEY_free(pkey);

    return store_info;
}