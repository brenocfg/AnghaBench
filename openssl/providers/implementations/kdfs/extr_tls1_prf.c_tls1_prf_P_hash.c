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
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  EVP_MAC_CTX ;
typedef  int /*<<< orphan*/  Ai ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_MAC_CTX_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_CTX_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_final (int /*<<< orphan*/ *,unsigned char*,size_t*,size_t) ; 
 int /*<<< orphan*/  EVP_MAC_init (int /*<<< orphan*/ *) ; 
 size_t EVP_MAC_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 

__attribute__((used)) static int tls1_prf_P_hash(EVP_MAC_CTX *ctx_init,
                           const unsigned char *sec, size_t sec_len,
                           const unsigned char *seed, size_t seed_len,
                           unsigned char *out, size_t olen)
{
    size_t chunk;
    EVP_MAC_CTX *ctx = NULL, *ctx_Ai = NULL;
    unsigned char Ai[EVP_MAX_MD_SIZE];
    size_t Ai_len;
    int ret = 0;
    OSSL_PARAM params[2], *p = params;

    *p++ = OSSL_PARAM_construct_octet_string(OSSL_MAC_PARAM_KEY,
                                             (void *)sec, sec_len);
    *p = OSSL_PARAM_construct_end();
    if (!EVP_MAC_CTX_set_params(ctx_init, params))
        goto err;
    if (!EVP_MAC_init(ctx_init))
        goto err;
    chunk = EVP_MAC_size(ctx_init);
    if (chunk == 0)
        goto err;
    /* A(0) = seed */
    ctx_Ai = EVP_MAC_CTX_dup(ctx_init);
    if (ctx_Ai == NULL)
        goto err;
    if (seed != NULL && !EVP_MAC_update(ctx_Ai, seed, seed_len))
        goto err;

    for (;;) {
        /* calc: A(i) = HMAC_<hash>(secret, A(i-1)) */
        if (!EVP_MAC_final(ctx_Ai, Ai, &Ai_len, sizeof(Ai)))
            goto err;
        EVP_MAC_CTX_free(ctx_Ai);
        ctx_Ai = NULL;

        /* calc next chunk: HMAC_<hash>(secret, A(i) + seed) */
        ctx = EVP_MAC_CTX_dup(ctx_init);
        if (ctx == NULL)
            goto err;
        if (!EVP_MAC_update(ctx, Ai, Ai_len))
            goto err;
        /* save state for calculating next A(i) value */
        if (olen > chunk) {
            ctx_Ai = EVP_MAC_CTX_dup(ctx);
            if (ctx_Ai == NULL)
                goto err;
        }
        if (seed != NULL && !EVP_MAC_update(ctx, seed, seed_len))
            goto err;
        if (olen <= chunk) {
            /* last chunk - use Ai as temp bounce buffer */
            if (!EVP_MAC_final(ctx, Ai, &Ai_len, sizeof(Ai)))
                goto err;
            memcpy(out, Ai, olen);
            break;
        }
        if (!EVP_MAC_final(ctx, out, NULL, olen))
            goto err;
        EVP_MAC_CTX_free(ctx);
        ctx = NULL;
        out += chunk;
        olen -= chunk;
    }
    ret = 1;
 err:
    EVP_MAC_CTX_free(ctx);
    EVP_MAC_CTX_free(ctx_Ai);
    OPENSSL_cleanse(Ai, sizeof(Ai));
    return ret;
}