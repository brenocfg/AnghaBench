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
typedef  int /*<<< orphan*/  uint8_t ;
struct crypto_tfm {int dummy; } ;
struct aes_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  CRYPTO_DIR_DECRYPT ; 
 struct aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  ifx_deu_aes (struct aes_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void aes_decrypt (struct crypto_tfm *tfm, uint8_t *out, const uint8_t *in)
{
    struct aes_ctx *ctx = crypto_tfm_ctx(tfm);
    ifx_deu_aes (ctx, out, in, NULL, AES_BLOCK_SIZE,
            CRYPTO_DIR_DECRYPT, 0);
}