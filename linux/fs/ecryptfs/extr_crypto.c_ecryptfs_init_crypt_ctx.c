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
struct ecryptfs_crypt_stat {int key_size; int /*<<< orphan*/  cs_tfm_mutex; int /*<<< orphan*/ * tfm; int /*<<< orphan*/  cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_FORBID_WEAK_KEYS ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * crypto_alloc_skcipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ecryptfs_crypto_api_algify_cipher_name (char**,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ecryptfs_printk (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

int ecryptfs_init_crypt_ctx(struct ecryptfs_crypt_stat *crypt_stat)
{
	char *full_alg_name;
	int rc = -EINVAL;

	ecryptfs_printk(KERN_DEBUG,
			"Initializing cipher [%s]; strlen = [%d]; "
			"key_size_bits = [%zd]\n",
			crypt_stat->cipher, (int)strlen(crypt_stat->cipher),
			crypt_stat->key_size << 3);
	mutex_lock(&crypt_stat->cs_tfm_mutex);
	if (crypt_stat->tfm) {
		rc = 0;
		goto out_unlock;
	}
	rc = ecryptfs_crypto_api_algify_cipher_name(&full_alg_name,
						    crypt_stat->cipher, "cbc");
	if (rc)
		goto out_unlock;
	crypt_stat->tfm = crypto_alloc_skcipher(full_alg_name, 0, 0);
	if (IS_ERR(crypt_stat->tfm)) {
		rc = PTR_ERR(crypt_stat->tfm);
		crypt_stat->tfm = NULL;
		ecryptfs_printk(KERN_ERR, "cryptfs: init_crypt_ctx(): "
				"Error initializing cipher [%s]\n",
				full_alg_name);
		goto out_free;
	}
	crypto_skcipher_set_flags(crypt_stat->tfm,
				  CRYPTO_TFM_REQ_FORBID_WEAK_KEYS);
	rc = 0;
out_free:
	kfree(full_alg_name);
out_unlock:
	mutex_unlock(&crypt_stat->cs_tfm_mutex);
	return rc;
}