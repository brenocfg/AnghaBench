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
struct md5_hmac_ctx {unsigned int keylen; int /*<<< orphan*/  key; } ;
struct deu_hash_t {int KIDX; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HASH_START ; 
 unsigned int MAX_HASH_KEYLEN ; 
 struct md5_hmac_ctx* crypto_shash_ctx (struct crypto_shash*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int md5_hmac_setkey(struct crypto_shash *tfm, const u8 *key, unsigned int keylen) 
{
    struct md5_hmac_ctx *mctx = crypto_shash_ctx(tfm);
    volatile struct deu_hash_t *hash = (struct deu_hash_t *) HASH_START;
    //printk("copying keys to context with length %d\n", keylen);

    if (keylen > MAX_HASH_KEYLEN) {
	printk("Key length more than what DEU hash can handle\n");
	return -EINVAL;
    }
 

    hash->KIDX |= 0x80000000; // reset all 16 words of the key to '0'
    memcpy(&mctx->key, key, keylen);
    mctx->keylen = keylen;

    return 0;

}