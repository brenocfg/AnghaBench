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
typedef  int /*<<< orphan*/  pem_password_cb ;
typedef  int /*<<< orphan*/  UI_METHOD ;
typedef  int /*<<< orphan*/  OSSL_STORE_INFO ;
typedef  int /*<<< orphan*/  OSSL_STORE_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_STORE_C_USE_SECMEM ; 
 scalar_t__ OSSL_STORE_INFO_PKEY ; 
 int /*<<< orphan*/  OSSL_STORE_INFO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OSSL_STORE_INFO_get1_PKEY (int /*<<< orphan*/ *) ; 
 scalar_t__ OSSL_STORE_INFO_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_STORE_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  OSSL_STORE_eof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OSSL_STORE_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UI_UTIL_wrap_read_pem_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_destroy_method (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_store_attach_pem_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  ossl_store_detach_pem_bio (int /*<<< orphan*/ *) ; 

EVP_PKEY *PEM_read_bio_PrivateKey(BIO *bp, EVP_PKEY **x, pem_password_cb *cb,
                                  void *u)
{
    EVP_PKEY *ret = NULL;
    OSSL_STORE_CTX *ctx = NULL;
    OSSL_STORE_INFO *info = NULL;
    UI_METHOD *ui_method = NULL;

    if ((ui_method = UI_UTIL_wrap_read_pem_callback(cb, 0)) == NULL)
        return NULL;

    if ((ctx = ossl_store_attach_pem_bio(bp, ui_method, u)) == NULL)
        goto err;
#ifndef OPENSSL_NO_SECURE_HEAP
    {
        int on = 1;
        if (!OSSL_STORE_ctrl(ctx, OSSL_STORE_C_USE_SECMEM, &on))
            goto err;
    }
#endif

    while (!OSSL_STORE_eof(ctx) && (info = OSSL_STORE_load(ctx)) != NULL) {
        if (OSSL_STORE_INFO_get_type(info) == OSSL_STORE_INFO_PKEY) {
            ret = OSSL_STORE_INFO_get1_PKEY(info);
            break;
        }
        OSSL_STORE_INFO_free(info);
    }

    if (ret != NULL && x != NULL)
        *x = ret;

 err:
    ossl_store_detach_pem_bio(ctx);
    UI_destroy_method(ui_method);
    OSSL_STORE_INFO_free(info);
    return ret;
}