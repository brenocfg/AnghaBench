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
struct user_namespace {int /*<<< orphan*/  keyring_sem; scalar_t__ persistent_keyring_register; } ;
struct keyring_index_key {char* description; int /*<<< orphan*/  desc_len; int /*<<< orphan*/ * type; } ;
struct key {long serial; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  scalar_t__ key_ref_t ;
typedef  int /*<<< orphan*/  index_key ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  KEY_NEED_LINK ; 
 long PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  current_cred () ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ find_key_to_update (scalar_t__,struct keyring_index_key*) ; 
 int from_kuid (struct user_namespace*,int /*<<< orphan*/ ) ; 
 scalar_t__ key_create_persistent (struct user_namespace*,int /*<<< orphan*/ ,struct keyring_index_key*) ; 
 long key_link (struct key*,struct key*) ; 
 int /*<<< orphan*/  key_ref_put (scalar_t__) ; 
 struct key* key_ref_to_ptr (scalar_t__) ; 
 int /*<<< orphan*/  key_set_index_key (struct keyring_index_key*) ; 
 int /*<<< orphan*/  key_set_timeout (struct key*,int /*<<< orphan*/ ) ; 
 long key_task_permission (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_type_keyring ; 
 scalar_t__ make_key_ref (scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct keyring_index_key*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  persistent_keyring_expiry ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long key_get_persistent(struct user_namespace *ns, kuid_t uid,
			       key_ref_t dest_ref)
{
	struct keyring_index_key index_key;
	struct key *persistent;
	key_ref_t reg_ref, persistent_ref;
	char buf[32];
	long ret;

	/* Look in the register if it exists */
	memset(&index_key, 0, sizeof(index_key));
	index_key.type = &key_type_keyring;
	index_key.description = buf;
	index_key.desc_len = sprintf(buf, "_persistent.%u", from_kuid(ns, uid));
	key_set_index_key(&index_key);

	if (ns->persistent_keyring_register) {
		reg_ref = make_key_ref(ns->persistent_keyring_register, true);
		down_read(&ns->keyring_sem);
		persistent_ref = find_key_to_update(reg_ref, &index_key);
		up_read(&ns->keyring_sem);

		if (persistent_ref)
			goto found;
	}

	/* It wasn't in the register, so we'll need to create it.  We might
	 * also need to create the register.
	 */
	down_write(&ns->keyring_sem);
	persistent_ref = key_create_persistent(ns, uid, &index_key);
	up_write(&ns->keyring_sem);
	if (!IS_ERR(persistent_ref))
		goto found;

	return PTR_ERR(persistent_ref);

found:
	ret = key_task_permission(persistent_ref, current_cred(), KEY_NEED_LINK);
	if (ret == 0) {
		persistent = key_ref_to_ptr(persistent_ref);
		ret = key_link(key_ref_to_ptr(dest_ref), persistent);
		if (ret == 0) {
			key_set_timeout(persistent, persistent_keyring_expiry);
			ret = persistent->serial;
		}
	}

	key_ref_put(persistent_ref);
	return ret;
}