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
struct user_namespace {int /*<<< orphan*/  keyring_sem; struct key* user_keyring_register; int /*<<< orphan*/  owner; } ;
struct key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_GID ; 
 int /*<<< orphan*/  IS_ERR (struct key*) ; 
 int KEY_POS_SEARCH ; 
 int KEY_POS_WRITE ; 
 int KEY_USR_READ ; 
 int KEY_USR_VIEW ; 
 struct key* READ_ONCE (struct key*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_cred ; 
 struct key* keyring_alloc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_store_release (struct key**,struct key*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct key *get_user_register(struct user_namespace *user_ns)
{
	struct key *reg_keyring = READ_ONCE(user_ns->user_keyring_register);

	if (reg_keyring)
		return reg_keyring;

	down_write(&user_ns->keyring_sem);

	/* Make sure there's a register keyring.  It gets owned by the
	 * user_namespace's owner.
	 */
	reg_keyring = user_ns->user_keyring_register;
	if (!reg_keyring) {
		reg_keyring = keyring_alloc(".user_reg",
					    user_ns->owner, INVALID_GID,
					    &init_cred,
					    KEY_POS_WRITE | KEY_POS_SEARCH |
					    KEY_USR_VIEW | KEY_USR_READ,
					    0,
					    NULL, NULL);
		if (!IS_ERR(reg_keyring))
			smp_store_release(&user_ns->user_keyring_register,
					  reg_keyring);
	}

	up_write(&user_ns->keyring_sem);

	/* We don't return a ref since the keyring is pinned by the user_ns */
	return reg_keyring;
}