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
typedef  int /*<<< orphan*/  uid_t ;
struct user_namespace {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  key_serial_t ;
typedef  int /*<<< orphan*/  key_ref_t ;
struct TYPE_2__ {int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SETUID ; 
 long EINVAL ; 
 long ENOTDIR ; 
 long EPERM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_LOOKUP_CREATE ; 
 int /*<<< orphan*/  KEY_NEED_WRITE ; 
 long PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_euid () ; 
 int /*<<< orphan*/  current_uid () ; 
 struct user_namespace* current_user_ns () ; 
 long key_get_persistent (struct user_namespace*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_ref_put (int /*<<< orphan*/ ) ; 
 TYPE_1__* key_ref_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_type_keyring ; 
 int /*<<< orphan*/  lookup_user_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_capable (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

long keyctl_get_persistent(uid_t _uid, key_serial_t destid)
{
	struct user_namespace *ns = current_user_ns();
	key_ref_t dest_ref;
	kuid_t uid;
	long ret;

	/* -1 indicates the current user */
	if (_uid == (uid_t)-1) {
		uid = current_uid();
	} else {
		uid = make_kuid(ns, _uid);
		if (!uid_valid(uid))
			return -EINVAL;

		/* You can only see your own persistent cache if you're not
		 * sufficiently privileged.
		 */
		if (!uid_eq(uid, current_uid()) &&
		    !uid_eq(uid, current_euid()) &&
		    !ns_capable(ns, CAP_SETUID))
			return -EPERM;
	}

	/* There must be a destination keyring */
	dest_ref = lookup_user_key(destid, KEY_LOOKUP_CREATE, KEY_NEED_WRITE);
	if (IS_ERR(dest_ref))
		return PTR_ERR(dest_ref);
	if (key_ref_to_ptr(dest_ref)->type != &key_type_keyring) {
		ret = -ENOTDIR;
		goto out_put_dest;
	}

	ret = key_get_persistent(ns, uid, dest_ref);

out_put_dest:
	key_ref_put(dest_ref);
	return ret;
}