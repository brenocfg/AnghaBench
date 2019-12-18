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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_key_length (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_DecryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned char*,unsigned char const*) ; 
 int /*<<< orphan*/  EVP_F_EVP_OPENINIT ; 
 scalar_t__ EVP_PKEY_RSA ; 
 int EVP_PKEY_decrypt_old (unsigned char*,unsigned char const*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_R_PUBLIC_KEY_NOT_RSA ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,int) ; 
 unsigned char* OPENSSL_malloc (int) ; 

int EVP_OpenInit(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *type,
                 const unsigned char *ek, int ekl, const unsigned char *iv,
                 EVP_PKEY *priv)
{
    unsigned char *key = NULL;
    int i, size = 0, ret = 0;

    if (type) {
        EVP_CIPHER_CTX_reset(ctx);
        if (!EVP_DecryptInit_ex(ctx, type, NULL, NULL, NULL))
            return 0;
    }

    if (priv == NULL)
        return 1;

    if (EVP_PKEY_id(priv) != EVP_PKEY_RSA) {
        EVPerr(EVP_F_EVP_OPENINIT, EVP_R_PUBLIC_KEY_NOT_RSA);
        goto err;
    }

    size = EVP_PKEY_size(priv);
    key = OPENSSL_malloc(size);
    if (key == NULL) {
        /* ERROR */
        EVPerr(EVP_F_EVP_OPENINIT, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    i = EVP_PKEY_decrypt_old(key, ek, ekl, priv);
    if ((i <= 0) || !EVP_CIPHER_CTX_set_key_length(ctx, i)) {
        /* ERROR */
        goto err;
    }
    if (!EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv))
        goto err;

    ret = 1;
 err:
    OPENSSL_clear_free(key, size);
    return ret;
}