#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UI_METHOD ;
typedef  int /*<<< orphan*/  OSSL_STORE_INFO ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/ * OSSL_STORE_INFO_new_PKEY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEM_STRING_PUBLIC ; 
 int /*<<< orphan*/ * d2i_PUBKEY (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OSSL_STORE_INFO *try_decode_PUBKEY(const char *pem_name,
                                          const char *pem_header,
                                          const unsigned char *blob,
                                          size_t len, void **pctx,
                                          int *matchcount,
                                          const UI_METHOD *ui_method,
                                          void *ui_data)
{
    OSSL_STORE_INFO *store_info = NULL;
    EVP_PKEY *pkey = NULL;

    if (pem_name != NULL) {
        if (strcmp(pem_name, PEM_STRING_PUBLIC) != 0)
            /* No match */
            return NULL;
        *matchcount = 1;
    }

    if ((pkey = d2i_PUBKEY(NULL, &blob, len)) != NULL) {
        *matchcount = 1;
        store_info = OSSL_STORE_INFO_new_PKEY(pkey);
    }

    return store_info;
}