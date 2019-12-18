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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_ablkcipher {int dummy; } ;
struct aes_ctx {int /*<<< orphan*/ * nonce; } ;
struct ablkcipher_request {int /*<<< orphan*/ * info; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_DIR_ENCRYPT ; 
 int CTR_RFC3686_IV_SIZE ; 
 int CTR_RFC3686_NONCE_SIZE ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct aes_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int lq_aes_queue_mgr (struct aes_ctx*,struct ablkcipher_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rfc3686_aes_encrypt(struct ablkcipher_request *areq)
{
    struct crypto_ablkcipher *cipher = crypto_ablkcipher_reqtfm(areq);
    struct aes_ctx *ctx = crypto_ablkcipher_ctx(cipher);
    int ret;
    u8 *info = areq->info;
    u8 rfc3686_iv[16];

    memcpy(rfc3686_iv, ctx->nonce, CTR_RFC3686_NONCE_SIZE);
    memcpy(rfc3686_iv + CTR_RFC3686_NONCE_SIZE, info, CTR_RFC3686_IV_SIZE);

    /* initialize counter portion of counter block */
    *(__be32 *)(rfc3686_iv + CTR_RFC3686_NONCE_SIZE + CTR_RFC3686_IV_SIZE) =
        cpu_to_be32(1);

    areq->info = rfc3686_iv;
    ret = lq_aes_queue_mgr(ctx, areq, areq->info, CRYPTO_DIR_ENCRYPT, 4);
    areq->info = info;
    return ret;
}