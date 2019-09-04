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
struct user_namespace {struct key* persistent_keyring_register; } ;
struct keyring_index_key {int /*<<< orphan*/  description; } ;
struct key {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  scalar_t__ key_ref_t ;

/* Variables and functions */
 scalar_t__ ERR_CAST (struct key*) ; 
 scalar_t__ ERR_PTR (long) ; 
 int /*<<< orphan*/  INVALID_GID ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_ALLOC_NOT_IN_QUOTA ; 
 int KEY_POS_ALL ; 
 int KEY_POS_SETATTR ; 
 int KEY_USR_READ ; 
 int KEY_USR_VIEW ; 
 int /*<<< orphan*/  current_cred () ; 
 scalar_t__ find_key_to_update (scalar_t__,struct keyring_index_key*) ; 
 long key_create_persistent_register (struct user_namespace*) ; 
 struct key* keyring_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct key*) ; 
 scalar_t__ make_key_ref (struct key*,int) ; 

__attribute__((used)) static key_ref_t key_create_persistent(struct user_namespace *ns, kuid_t uid,
				       struct keyring_index_key *index_key)
{
	struct key *persistent;
	key_ref_t reg_ref, persistent_ref;

	if (!ns->persistent_keyring_register) {
		long err = key_create_persistent_register(ns);
		if (err < 0)
			return ERR_PTR(err);
	} else {
		reg_ref = make_key_ref(ns->persistent_keyring_register, true);
		persistent_ref = find_key_to_update(reg_ref, index_key);
		if (persistent_ref)
			return persistent_ref;
	}

	persistent = keyring_alloc(index_key->description,
				   uid, INVALID_GID, current_cred(),
				   ((KEY_POS_ALL & ~KEY_POS_SETATTR) |
				    KEY_USR_VIEW | KEY_USR_READ),
				   KEY_ALLOC_NOT_IN_QUOTA, NULL,
				   ns->persistent_keyring_register);
	if (IS_ERR(persistent))
		return ERR_CAST(persistent);

	return make_key_ref(persistent, true);
}