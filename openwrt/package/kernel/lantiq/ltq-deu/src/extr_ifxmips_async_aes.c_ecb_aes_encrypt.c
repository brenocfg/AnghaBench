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
struct crypto_ablkcipher {int dummy; } ;
struct aes_ctx {int dummy; } ;
struct ablkcipher_request {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_DIR_ENCRYPT ; 
 struct aes_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int lq_aes_queue_mgr (struct aes_ctx*,struct ablkcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecb_aes_encrypt (struct ablkcipher_request *areq)
{
    struct crypto_ablkcipher *cipher = crypto_ablkcipher_reqtfm(areq);
    struct aes_ctx *ctx = crypto_ablkcipher_ctx(cipher);

    return lq_aes_queue_mgr(ctx, areq, areq->info, CRYPTO_DIR_ENCRYPT, 0);

}