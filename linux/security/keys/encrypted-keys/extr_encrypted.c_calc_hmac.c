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
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int PTR_ERR (struct crypto_shash*) ; 
 int calc_hash (struct crypto_shash*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 struct crypto_shash* crypto_alloc_shash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (struct crypto_shash*) ; 
 int crypto_shash_setkey (struct crypto_shash*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  hmac_alg ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int calc_hmac(u8 *digest, const u8 *key, unsigned int keylen,
		     const u8 *buf, unsigned int buflen)
{
	struct crypto_shash *tfm;
	int err;

	tfm = crypto_alloc_shash(hmac_alg, 0, 0);
	if (IS_ERR(tfm)) {
		pr_err("encrypted_key: can't alloc %s transform: %ld\n",
		       hmac_alg, PTR_ERR(tfm));
		return PTR_ERR(tfm);
	}

	err = crypto_shash_setkey(tfm, key, keylen);
	if (!err)
		err = calc_hash(tfm, digest, buf, buflen);
	crypto_free_shash(tfm);
	return err;
}