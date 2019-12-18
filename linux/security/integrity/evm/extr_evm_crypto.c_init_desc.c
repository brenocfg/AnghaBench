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
typedef  size_t uint8_t ;
struct shash_desc {struct crypto_shash* tfm; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_NOLOAD ; 
 long EINVAL ; 
 long ENOKEY ; 
 long ENOMEM ; 
 struct shash_desc* ERR_PTR (long) ; 
 int EVM_INIT_HMAC ; 
 char EVM_XATTR_HMAC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t HASH_ALGO__LAST ; 
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 long PTR_ERR (struct crypto_shash*) ; 
 struct crypto_shash* crypto_alloc_shash (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (struct crypto_shash*) ; 
 scalar_t__ crypto_shash_descsize (struct crypto_shash*) ; 
 long crypto_shash_init (struct shash_desc*) ; 
 long crypto_shash_setkey (struct crypto_shash*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* evm_hmac ; 
 int evm_initialized ; 
 struct crypto_shash** evm_tfm ; 
 int /*<<< orphan*/  evmkey ; 
 int /*<<< orphan*/  evmkey_len ; 
 char** hash_algo_name ; 
 struct crypto_shash* hmac_tfm ; 
 int /*<<< orphan*/  kfree (struct shash_desc*) ; 
 struct shash_desc* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,long) ; 
 int /*<<< orphan*/  pr_err_once (char*) ; 

__attribute__((used)) static struct shash_desc *init_desc(char type, uint8_t hash_algo)
{
	long rc;
	const char *algo;
	struct crypto_shash **tfm;
	struct shash_desc *desc;

	if (type == EVM_XATTR_HMAC) {
		if (!(evm_initialized & EVM_INIT_HMAC)) {
			pr_err_once("HMAC key is not set\n");
			return ERR_PTR(-ENOKEY);
		}
		tfm = &hmac_tfm;
		algo = evm_hmac;
	} else {
		if (hash_algo >= HASH_ALGO__LAST)
			return ERR_PTR(-EINVAL);

		tfm = &evm_tfm[hash_algo];
		algo = hash_algo_name[hash_algo];
	}

	if (*tfm == NULL) {
		mutex_lock(&mutex);
		if (*tfm)
			goto out;
		*tfm = crypto_alloc_shash(algo, 0, CRYPTO_NOLOAD);
		if (IS_ERR(*tfm)) {
			rc = PTR_ERR(*tfm);
			pr_err("Can not allocate %s (reason: %ld)\n", algo, rc);
			*tfm = NULL;
			mutex_unlock(&mutex);
			return ERR_PTR(rc);
		}
		if (type == EVM_XATTR_HMAC) {
			rc = crypto_shash_setkey(*tfm, evmkey, evmkey_len);
			if (rc) {
				crypto_free_shash(*tfm);
				*tfm = NULL;
				mutex_unlock(&mutex);
				return ERR_PTR(rc);
			}
		}
out:
		mutex_unlock(&mutex);
	}

	desc = kmalloc(sizeof(*desc) + crypto_shash_descsize(*tfm),
			GFP_KERNEL);
	if (!desc)
		return ERR_PTR(-ENOMEM);

	desc->tfm = *tfm;

	rc = crypto_shash_init(desc);
	if (rc) {
		kfree(desc);
		return ERR_PTR(rc);
	}
	return desc;
}