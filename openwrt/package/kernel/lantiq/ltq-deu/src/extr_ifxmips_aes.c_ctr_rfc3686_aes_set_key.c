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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_tfm {int /*<<< orphan*/  crt_flags; } ;
struct aes_ctx {unsigned int key_length; scalar_t__ buf; int /*<<< orphan*/ * nonce; } ;

/* Variables and functions */
 unsigned long CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 unsigned int CTR_RFC3686_NONCE_SIZE ; 
 int EINVAL ; 
 struct aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 

int ctr_rfc3686_aes_set_key (struct crypto_tfm *tfm, const uint8_t *in_key, unsigned int key_len)
{
    struct aes_ctx *ctx = crypto_tfm_ctx(tfm);
    unsigned long *flags = (unsigned long *)&tfm->crt_flags;

    //printk("ctr_rfc3686_aes_set_key in %s\n", __FILE__);

    memcpy(ctx->nonce, in_key + (key_len - CTR_RFC3686_NONCE_SIZE),
           CTR_RFC3686_NONCE_SIZE);

    key_len -= CTR_RFC3686_NONCE_SIZE; // remove 4 bytes of nonce

    if (key_len != 16 && key_len != 24 && key_len != 32) {
        *flags |= CRYPTO_TFM_RES_BAD_KEY_LEN;
        return -EINVAL;
    }

    ctx->key_length = key_len;
    
    memcpy ((u8 *) (ctx->buf), in_key, key_len);

    return 0;
}