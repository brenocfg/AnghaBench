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
typedef  int /*<<< orphan*/  OSSL_STORE_INFO ;
typedef  int /*<<< orphan*/  OSSL_STORE_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ OSSL_STORE_INFO_PARAMS ; 
 int /*<<< orphan*/  OSSL_STORE_INFO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OSSL_STORE_INFO_get1_PARAMS (int /*<<< orphan*/ *) ; 
 scalar_t__ OSSL_STORE_INFO_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_STORE_eof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OSSL_STORE_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UI_null () ; 
 int /*<<< orphan*/ * ossl_store_attach_pem_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_store_detach_pem_bio (int /*<<< orphan*/ *) ; 

EVP_PKEY *PEM_read_bio_Parameters(BIO *bp, EVP_PKEY **x)
{
    EVP_PKEY *ret = NULL;
    OSSL_STORE_CTX *ctx = NULL;
    OSSL_STORE_INFO *info = NULL;

    if ((ctx = ossl_store_attach_pem_bio(bp, UI_null(), NULL)) == NULL)
        goto err;

    while (!OSSL_STORE_eof(ctx) && (info = OSSL_STORE_load(ctx)) != NULL) {
        if (OSSL_STORE_INFO_get_type(info) == OSSL_STORE_INFO_PARAMS) {
            ret = OSSL_STORE_INFO_get1_PARAMS(info);
            break;
        }
        OSSL_STORE_INFO_free(info);
    }

    if (ret != NULL && x != NULL)
        *x = ret;

 err:
    ossl_store_detach_pem_bio(ctx);
    OSSL_STORE_INFO_free(info);
    return ret;
}