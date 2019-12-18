#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct fscrypt_master_key** data; } ;
struct key {TYPE_1__ payload; } ;
struct fscrypt_master_key {int /*<<< orphan*/  mk_refcount; int /*<<< orphan*/  mk_decrypted_inodes_lock; } ;
struct fscrypt_info {int /*<<< orphan*/  ci_master_key_link; struct key* ci_master_key; int /*<<< orphan*/ * ci_essiv_tfm; int /*<<< orphan*/ * ci_ctfm; int /*<<< orphan*/  ci_policy; scalar_t__ ci_direct_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_free_skcipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscrypt_info_cachep ; 
 int /*<<< orphan*/  fscrypt_is_direct_key_policy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscrypt_put_direct_key (scalar_t__) ; 
 int /*<<< orphan*/  key_invalidate (struct key*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fscrypt_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_crypt_info(struct fscrypt_info *ci)
{
	struct key *key;

	if (!ci)
		return;

	if (ci->ci_direct_key) {
		fscrypt_put_direct_key(ci->ci_direct_key);
	} else if ((ci->ci_ctfm != NULL || ci->ci_essiv_tfm != NULL) &&
		   !fscrypt_is_direct_key_policy(&ci->ci_policy)) {
		crypto_free_skcipher(ci->ci_ctfm);
		crypto_free_cipher(ci->ci_essiv_tfm);
	}

	key = ci->ci_master_key;
	if (key) {
		struct fscrypt_master_key *mk = key->payload.data[0];

		/*
		 * Remove this inode from the list of inodes that were unlocked
		 * with the master key.
		 *
		 * In addition, if we're removing the last inode from a key that
		 * already had its secret removed, invalidate the key so that it
		 * gets removed from ->s_master_keys.
		 */
		spin_lock(&mk->mk_decrypted_inodes_lock);
		list_del(&ci->ci_master_key_link);
		spin_unlock(&mk->mk_decrypted_inodes_lock);
		if (refcount_dec_and_test(&mk->mk_refcount))
			key_invalidate(key);
		key_put(key);
	}
	kmem_cache_free(fscrypt_info_cachep, ci);
}