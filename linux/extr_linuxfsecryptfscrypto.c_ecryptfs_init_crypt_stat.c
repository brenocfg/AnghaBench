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
struct ecryptfs_crypt_stat {int /*<<< orphan*/  flags; struct crypto_shash* hash_tfm; int /*<<< orphan*/  cs_tfm_mutex; int /*<<< orphan*/  cs_mutex; int /*<<< orphan*/  keysig_list_mutex; int /*<<< orphan*/  keysig_list; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECRYPTFS_DEFAULT_HASH ; 
 int /*<<< orphan*/  ECRYPTFS_STRUCT_INITIALIZED ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int PTR_ERR (struct crypto_shash*) ; 
 struct crypto_shash* crypto_alloc_shash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecryptfs_printk (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int ecryptfs_init_crypt_stat(struct ecryptfs_crypt_stat *crypt_stat)
{
	struct crypto_shash *tfm;
	int rc;

	tfm = crypto_alloc_shash(ECRYPTFS_DEFAULT_HASH, 0, 0);
	if (IS_ERR(tfm)) {
		rc = PTR_ERR(tfm);
		ecryptfs_printk(KERN_ERR, "Error attempting to "
				"allocate crypto context; rc = [%d]\n",
				rc);
		return rc;
	}

	memset((void *)crypt_stat, 0, sizeof(struct ecryptfs_crypt_stat));
	INIT_LIST_HEAD(&crypt_stat->keysig_list);
	mutex_init(&crypt_stat->keysig_list_mutex);
	mutex_init(&crypt_stat->cs_mutex);
	mutex_init(&crypt_stat->cs_tfm_mutex);
	crypt_stat->hash_tfm = tfm;
	crypt_stat->flags |= ECRYPTFS_STRUCT_INITIALIZED;

	return 0;
}