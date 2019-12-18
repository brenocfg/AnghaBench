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
struct super_block {int /*<<< orphan*/  s_master_keys; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;
struct key {int /*<<< orphan*/  sem; TYPE_1__ payload; } ;
struct fscrypt_master_key_secret {int dummy; } ;
struct fscrypt_key_specifier {int dummy; } ;
typedef  int /*<<< orphan*/  DEFINE_MUTEX ;

/* Variables and functions */
 int ENOKEY ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int KEY_DEAD ; 
 int PTR_ERR (struct key*) ; 
 int add_existing_master_key (int /*<<< orphan*/ ,struct fscrypt_master_key_secret*) ; 
 int add_new_master_key (struct fscrypt_master_key_secret*,struct fscrypt_key_specifier const*,int /*<<< orphan*/ ) ; 
 int allocate_filesystem_keyring (struct super_block*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct key* fscrypt_find_master_key (struct super_block*,struct fscrypt_key_specifier const*) ; 
 int /*<<< orphan*/  key_invalidate (struct key*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_master_key(struct super_block *sb,
			  struct fscrypt_master_key_secret *secret,
			  const struct fscrypt_key_specifier *mk_spec)
{
	static DEFINE_MUTEX(fscrypt_add_key_mutex);
	struct key *key;
	int err;

	mutex_lock(&fscrypt_add_key_mutex); /* serialize find + link */
retry:
	key = fscrypt_find_master_key(sb, mk_spec);
	if (IS_ERR(key)) {
		err = PTR_ERR(key);
		if (err != -ENOKEY)
			goto out_unlock;
		/* Didn't find the key in ->s_master_keys.  Add it. */
		err = allocate_filesystem_keyring(sb);
		if (err)
			goto out_unlock;
		err = add_new_master_key(secret, mk_spec, sb->s_master_keys);
	} else {
		/*
		 * Found the key in ->s_master_keys.  Re-add the secret if
		 * needed, and add the user to ->mk_users if needed.
		 */
		down_write(&key->sem);
		err = add_existing_master_key(key->payload.data[0], secret);
		up_write(&key->sem);
		if (err == KEY_DEAD) {
			/* Key being removed or needs to be removed */
			key_invalidate(key);
			key_put(key);
			goto retry;
		}
		key_put(key);
	}
out_unlock:
	mutex_unlock(&fscrypt_add_key_mutex);
	return err;
}