#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__ ki_len; size_t iv_len; int /*<<< orphan*/  context_len; int /*<<< orphan*/  context; int /*<<< orphan*/  label_len; int /*<<< orphan*/  label; int /*<<< orphan*/  iv; int /*<<< orphan*/  mode; int /*<<< orphan*/ * ctx_init; int /*<<< orphan*/ * ki; } ;
typedef  TYPE_1__ KBKDF ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t EVP_MAC_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,size_t) ; 
 unsigned char* OPENSSL_zalloc (size_t) ; 
 int /*<<< orphan*/  PROV_R_INVALID_SEED_LENGTH ; 
 int /*<<< orphan*/  PROV_R_MISSING_MAC ; 
 int /*<<< orphan*/  PROV_R_NO_KEY_SET ; 
 int /*<<< orphan*/  be32 (size_t) ; 
 int derive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t,int /*<<< orphan*/ ,unsigned char*,size_t) ; 

__attribute__((used)) static int kbkdf_derive(void *vctx, unsigned char *key, size_t keylen)
{
    KBKDF *ctx = (KBKDF *)vctx;
    int ret = 0;
    unsigned char *k_i = NULL;
    uint32_t l = be32(keylen * 8);
    size_t h = 0;

    /* label, context, and iv are permitted to be empty.  Check everything
     * else. */
    if (ctx->ctx_init == NULL) {
        if (ctx->ki_len == 0 || ctx->ki == NULL) {
            ERR_raise(ERR_LIB_PROV, PROV_R_NO_KEY_SET);
            return 0;
        }
        /* Could either be missing MAC or missing message digest or missing
         * cipher - arbitrarily, I pick this one. */
        ERR_raise(ERR_LIB_PROV, PROV_R_MISSING_MAC);
        return 0;
    }

    h = EVP_MAC_size(ctx->ctx_init);
    if (h == 0)
        goto done;
    if (ctx->iv_len != 0 && ctx->iv_len != h) {
        ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_SEED_LENGTH);
        goto done;
    }

    k_i = OPENSSL_zalloc(h);
    if (k_i == NULL)
        goto done;

    ret = derive(ctx->ctx_init, ctx->mode, ctx->iv, ctx->iv_len, ctx->label,
                 ctx->label_len, ctx->context, ctx->context_len, k_i, h, l,
                 key, keylen);
done:
    if (ret != 1)
        OPENSSL_cleanse(key, keylen);
    OPENSSL_clear_free(k_i, h);
    return ret;
}