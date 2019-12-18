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
struct TYPE_4__ {int pkey_flags; scalar_t__ (* param_decode ) (int /*<<< orphan*/ *,unsigned char const**,size_t) ;int /*<<< orphan*/  pkey_id; } ;
typedef  int /*<<< orphan*/  OSSL_STORE_INFO ;
typedef  TYPE_1__ EVP_PKEY_ASN1_METHOD ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int ASN1_PKEY_ALIAS ; 
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
 TYPE_1__* EVP_PKEY_asn1_get0 (int) ; 
 int EVP_PKEY_asn1_get_count () ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* EVP_PKEY_get0_asn1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 scalar_t__ EVP_PKEY_set_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_PKEY_set_type_str (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  OSSL_STORE_F_TRY_DECODE_PARAMS ; 
 int /*<<< orphan*/ * OSSL_STORE_INFO_new_PARAMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pem_check_suffix (char const*,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 

__attribute__((used)) static OSSL_STORE_INFO *try_decode_params(const char *pem_name,
                                          const char *pem_header,
                                          const unsigned char *blob,
                                          size_t len, void **pctx,
                                          int *matchcount,
                                          const UI_METHOD *ui_method,
                                          void *ui_data)
{
    OSSL_STORE_INFO *store_info = NULL;
    int slen = 0;
    EVP_PKEY *pkey = NULL;
    const EVP_PKEY_ASN1_METHOD *ameth = NULL;
    int ok = 0;

    if (pem_name != NULL) {
        if ((slen = pem_check_suffix(pem_name, "PARAMETERS")) == 0)
            return NULL;
        *matchcount = 1;
    }

    if (slen > 0) {
        if ((pkey = EVP_PKEY_new()) == NULL) {
            OSSL_STOREerr(OSSL_STORE_F_TRY_DECODE_PARAMS, ERR_R_EVP_LIB);
            return NULL;
        }


        if (EVP_PKEY_set_type_str(pkey, pem_name, slen)
            && (ameth = EVP_PKEY_get0_asn1(pkey)) != NULL
            && ameth->param_decode != NULL
            && ameth->param_decode(pkey, &blob, len))
            ok = 1;
    } else {
        int i;
        EVP_PKEY *tmp_pkey = NULL;

        for (i = 0; i < EVP_PKEY_asn1_get_count(); i++) {
            const unsigned char *tmp_blob = blob;

            if (tmp_pkey == NULL && (tmp_pkey = EVP_PKEY_new()) == NULL) {
                OSSL_STOREerr(OSSL_STORE_F_TRY_DECODE_PARAMS, ERR_R_EVP_LIB);
                break;
            }

            ameth = EVP_PKEY_asn1_get0(i);
            if (ameth->pkey_flags & ASN1_PKEY_ALIAS)
                continue;

            if (EVP_PKEY_set_type(tmp_pkey, ameth->pkey_id)
                && (ameth = EVP_PKEY_get0_asn1(tmp_pkey)) != NULL
                && ameth->param_decode != NULL
                && ameth->param_decode(tmp_pkey, &tmp_blob, len)) {
                if (pkey != NULL)
                    EVP_PKEY_free(tmp_pkey);
                else
                    pkey = tmp_pkey;
                tmp_pkey = NULL;
                (*matchcount)++;
            }
        }

        EVP_PKEY_free(tmp_pkey);
        if (*matchcount == 1) {
            ok = 1;
        }
    }

    if (ok)
        store_info = OSSL_STORE_INFO_new_PARAMS(pkey);
    if (store_info == NULL)
        EVP_PKEY_free(pkey);

    return store_info;
}