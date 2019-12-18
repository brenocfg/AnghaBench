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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  EVP_F_EVP_SIGNFINAL ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_FINALISE ; 
 int EVP_MD_CTX_copy_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_md (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 scalar_t__ EVP_MD_CTX_test_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_CTX_set_signature_md (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_PKEY_sign (int /*<<< orphan*/ *,unsigned char*,size_t*,unsigned char*,unsigned int) ; 
 scalar_t__ EVP_PKEY_sign_init (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int EVP_SignFinal(EVP_MD_CTX *ctx, unsigned char *sigret,
                  unsigned int *siglen, EVP_PKEY *pkey)
{
    unsigned char m[EVP_MAX_MD_SIZE];
    unsigned int m_len = 0;
    int i = 0;
    size_t sltmp;
    EVP_PKEY_CTX *pkctx = NULL;

    *siglen = 0;
    if (EVP_MD_CTX_test_flags(ctx, EVP_MD_CTX_FLAG_FINALISE)) {
        if (!EVP_DigestFinal_ex(ctx, m, &m_len))
            goto err;
    } else {
        int rv = 0;
        EVP_MD_CTX *tmp_ctx = EVP_MD_CTX_new();
        if (tmp_ctx == NULL) {
            EVPerr(EVP_F_EVP_SIGNFINAL, ERR_R_MALLOC_FAILURE);
            return 0;
        }
        rv = EVP_MD_CTX_copy_ex(tmp_ctx, ctx);
        if (rv)
            rv = EVP_DigestFinal_ex(tmp_ctx, m, &m_len);
        EVP_MD_CTX_free(tmp_ctx);
        if (!rv)
            return 0;
    }

    sltmp = (size_t)EVP_PKEY_size(pkey);
    i = 0;
    pkctx = EVP_PKEY_CTX_new(pkey, NULL);
    if (pkctx == NULL)
        goto err;
    if (EVP_PKEY_sign_init(pkctx) <= 0)
        goto err;
    if (EVP_PKEY_CTX_set_signature_md(pkctx, EVP_MD_CTX_md(ctx)) <= 0)
        goto err;
    if (EVP_PKEY_sign(pkctx, sigret, &sltmp, m, m_len) <= 0)
        goto err;
    *siglen = sltmp;
    i = 1;
 err:
    EVP_PKEY_CTX_free(pkctx);
    return i;
}