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
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_MAC_CTX ;
typedef  int /*<<< orphan*/  A1 ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_FLAGS ; 
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_KEY ; 
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_MD ; 
 int /*<<< orphan*/  EVP_MAC_CTX_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MAC_CTX_new_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MAC_HMAC ; 
 int EVP_MAC_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char const*,...) ; 
 int /*<<< orphan*/  EVP_MAC_final (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 int /*<<< orphan*/  EVP_MAC_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_NON_FIPS_ALLOW ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 

__attribute__((used)) static int tls1_prf_P_hash(const EVP_MD *md,
                           const unsigned char *sec, size_t sec_len,
                           const unsigned char *seed, size_t seed_len,
                           unsigned char *out, size_t olen)
{
    int chunk;
    EVP_MAC_CTX *ctx = NULL, *ctx_tmp = NULL, *ctx_init = NULL;
    unsigned char A1[EVP_MAX_MD_SIZE];
    size_t A1_len;
    int ret = 0;

    chunk = EVP_MD_size(md);
    if (!ossl_assert(chunk > 0))
        goto err;

    ctx = EVP_MAC_CTX_new_id(EVP_MAC_HMAC);
    ctx_tmp = EVP_MAC_CTX_new_id(EVP_MAC_HMAC);
    ctx_init = EVP_MAC_CTX_new_id(EVP_MAC_HMAC);
    if (ctx == NULL || ctx_tmp == NULL || ctx_init == NULL)
        goto err;
    if (EVP_MAC_ctrl(ctx_init, EVP_MAC_CTRL_SET_FLAGS, EVP_MD_CTX_FLAG_NON_FIPS_ALLOW) != 1)
        goto err;
    if (EVP_MAC_ctrl(ctx_init, EVP_MAC_CTRL_SET_MD, md) != 1)
        goto err;
    if (EVP_MAC_ctrl(ctx_init, EVP_MAC_CTRL_SET_KEY, sec, sec_len) != 1)
        goto err;
    if (!EVP_MAC_init(ctx_init))
        goto err;
    if (!EVP_MAC_CTX_copy(ctx, ctx_init))
        goto err;
    if (seed != NULL && !EVP_MAC_update(ctx, seed, seed_len))
        goto err;
    if (!EVP_MAC_final(ctx, A1, &A1_len))
        goto err;

    for (;;) {
        /* Reinit mac contexts */
        if (!EVP_MAC_CTX_copy(ctx, ctx_init))
            goto err;
        if (!EVP_MAC_update(ctx, A1, A1_len))
            goto err;
        if (olen > (size_t)chunk && !EVP_MAC_CTX_copy(ctx_tmp, ctx))
            goto err;
        if (seed != NULL && !EVP_MAC_update(ctx, seed, seed_len))
            goto err;

        if (olen > (size_t)chunk) {
            size_t mac_len;
            if (!EVP_MAC_final(ctx, out, &mac_len))
                goto err;
            out += mac_len;
            olen -= mac_len;
            /* calc the next A1 value */
            if (!EVP_MAC_final(ctx_tmp, A1, &A1_len))
                goto err;
        } else {                /* last one */

            if (!EVP_MAC_final(ctx, A1, &A1_len))
                goto err;
            memcpy(out, A1, olen);
            break;
        }
    }
    ret = 1;
 err:
    EVP_MAC_CTX_free(ctx);
    EVP_MAC_CTX_free(ctx_tmp);
    EVP_MAC_CTX_free(ctx_init);
    OPENSSL_cleanse(A1, sizeof(A1));
    return ret;
}