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
struct inode {int dummy; } ;
typedef  struct fsverity_hash_alg {unsigned int name; scalar_t__ digest_size; scalar_t__ block_size; int /*<<< orphan*/  tfm; } const fsverity_hash_alg ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct fsverity_hash_alg const*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int ENOPKG ; 
 struct fsverity_hash_alg const* ERR_CAST (struct crypto_ahash*) ; 
 struct fsverity_hash_alg const* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct crypto_ahash*) ; 
 int /*<<< orphan*/  PTR_ERR (struct crypto_ahash*) ; 
 struct crypto_ahash* READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/ * cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct crypto_ahash*) ; 
 scalar_t__ crypto_ahash_blocksize (struct crypto_ahash*) ; 
 scalar_t__ crypto_ahash_digestsize (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_ahash_driver_name (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_alloc_ahash (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_ahash (struct crypto_ahash*) ; 
 int /*<<< orphan*/  fsverity_err (struct inode const*,char*,unsigned int,int /*<<< orphan*/ ) ; 
 struct fsverity_hash_alg const* fsverity_hash_algs ; 
 int /*<<< orphan*/  fsverity_warn (struct inode const*,char*,unsigned int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,int /*<<< orphan*/ ) ; 

const struct fsverity_hash_alg *fsverity_get_hash_alg(const struct inode *inode,
						      unsigned int num)
{
	struct fsverity_hash_alg *alg;
	struct crypto_ahash *tfm;
	int err;

	if (num >= ARRAY_SIZE(fsverity_hash_algs) ||
	    !fsverity_hash_algs[num].name) {
		fsverity_warn(inode, "Unknown hash algorithm number: %u", num);
		return ERR_PTR(-EINVAL);
	}
	alg = &fsverity_hash_algs[num];

	/* pairs with cmpxchg() below */
	tfm = READ_ONCE(alg->tfm);
	if (likely(tfm != NULL))
		return alg;
	/*
	 * Using the shash API would make things a bit simpler, but the ahash
	 * API is preferable as it allows the use of crypto accelerators.
	 */
	tfm = crypto_alloc_ahash(alg->name, 0, 0);
	if (IS_ERR(tfm)) {
		if (PTR_ERR(tfm) == -ENOENT) {
			fsverity_warn(inode,
				      "Missing crypto API support for hash algorithm \"%s\"",
				      alg->name);
			return ERR_PTR(-ENOPKG);
		}
		fsverity_err(inode,
			     "Error allocating hash algorithm \"%s\": %ld",
			     alg->name, PTR_ERR(tfm));
		return ERR_CAST(tfm);
	}

	err = -EINVAL;
	if (WARN_ON(alg->digest_size != crypto_ahash_digestsize(tfm)))
		goto err_free_tfm;
	if (WARN_ON(alg->block_size != crypto_ahash_blocksize(tfm)))
		goto err_free_tfm;

	pr_info("%s using implementation \"%s\"\n",
		alg->name, crypto_ahash_driver_name(tfm));

	/* pairs with READ_ONCE() above */
	if (cmpxchg(&alg->tfm, NULL, tfm) != NULL)
		crypto_free_ahash(tfm);

	return alg;

err_free_tfm:
	crypto_free_ahash(tfm);
	return ERR_PTR(err);
}