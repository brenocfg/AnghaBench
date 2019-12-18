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
struct key {int dummy; } ;
struct fscrypt_master_key_secret {int dummy; } ;
struct fscrypt_master_key {int /*<<< orphan*/  mk_secret_sem; int /*<<< orphan*/  mk_secret; int /*<<< orphan*/  mk_refcount; scalar_t__ mk_users; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOKEY ; 
 struct key* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int KEY_DEAD ; 
 int PTR_ERR (struct key*) ; 
 int add_master_key_user (struct fscrypt_master_key*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct key* find_master_key_user (struct fscrypt_master_key*) ; 
 int /*<<< orphan*/  is_master_key_secret_present (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  move_master_key_secret (int /*<<< orphan*/ *,struct fscrypt_master_key_secret*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_existing_master_key(struct fscrypt_master_key *mk,
				   struct fscrypt_master_key_secret *secret)
{
	struct key *mk_user;
	bool rekey;
	int err;

	/*
	 * If the current user is already in ->mk_users, then there's nothing to
	 * do.  (Not applicable for v1 policy keys, which have NULL ->mk_users.)
	 */
	if (mk->mk_users) {
		mk_user = find_master_key_user(mk);
		if (mk_user != ERR_PTR(-ENOKEY)) {
			if (IS_ERR(mk_user))
				return PTR_ERR(mk_user);
			key_put(mk_user);
			return 0;
		}
	}

	/* If we'll be re-adding ->mk_secret, try to take the reference. */
	rekey = !is_master_key_secret_present(&mk->mk_secret);
	if (rekey && !refcount_inc_not_zero(&mk->mk_refcount))
		return KEY_DEAD;

	/* Add the current user to ->mk_users, if applicable. */
	if (mk->mk_users) {
		err = add_master_key_user(mk);
		if (err) {
			if (rekey && refcount_dec_and_test(&mk->mk_refcount))
				return KEY_DEAD;
			return err;
		}
	}

	/* Re-add the secret if needed. */
	if (rekey) {
		down_write(&mk->mk_secret_sem);
		move_master_key_secret(&mk->mk_secret, secret);
		up_write(&mk->mk_secret_sem);
	}
	return 0;
}