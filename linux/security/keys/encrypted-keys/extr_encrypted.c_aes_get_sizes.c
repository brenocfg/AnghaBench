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
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 scalar_t__ IS_ERR (struct crypto_skcipher*) ; 
 int PTR_ERR (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  blkcipher_alg ; 
 int /*<<< orphan*/  blksize ; 
 struct crypto_skcipher* crypto_alloc_skcipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_skcipher (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_blocksize (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_ivsize (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  ivsize ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int aes_get_sizes(void)
{
	struct crypto_skcipher *tfm;

	tfm = crypto_alloc_skcipher(blkcipher_alg, 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(tfm)) {
		pr_err("encrypted_key: failed to alloc_cipher (%ld)\n",
		       PTR_ERR(tfm));
		return PTR_ERR(tfm);
	}
	ivsize = crypto_skcipher_ivsize(tfm);
	blksize = crypto_skcipher_blocksize(tfm);
	crypto_free_skcipher(tfm);
	return 0;
}