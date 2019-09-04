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
struct cred {int /*<<< orphan*/  cap_permitted; int /*<<< orphan*/  cap_effective; int /*<<< orphan*/  fsuid; int /*<<< orphan*/  user_ns; } ;
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 int EINVAL ; 
#define  LSM_SETID_FS 131 
#define  LSM_SETID_ID 130 
#define  LSM_SETID_RE 129 
#define  LSM_SETID_RES 128 
 int /*<<< orphan*/  SECURE_NO_SETUID_FIXUP ; 
 int /*<<< orphan*/  cap_drop_fs_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_emulate_setxuid (struct cred*,struct cred const*) ; 
 int /*<<< orphan*/  cap_raise_fs_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  issecure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cap_task_fix_setuid(struct cred *new, const struct cred *old, int flags)
{
	switch (flags) {
	case LSM_SETID_RE:
	case LSM_SETID_ID:
	case LSM_SETID_RES:
		/* juggle the capabilities to follow [RES]UID changes unless
		 * otherwise suppressed */
		if (!issecure(SECURE_NO_SETUID_FIXUP))
			cap_emulate_setxuid(new, old);
		break;

	case LSM_SETID_FS:
		/* juggle the capabilties to follow FSUID changes, unless
		 * otherwise suppressed
		 *
		 * FIXME - is fsuser used for all CAP_FS_MASK capabilities?
		 *          if not, we might be a bit too harsh here.
		 */
		if (!issecure(SECURE_NO_SETUID_FIXUP)) {
			kuid_t root_uid = make_kuid(old->user_ns, 0);
			if (uid_eq(old->fsuid, root_uid) && !uid_eq(new->fsuid, root_uid))
				new->cap_effective =
					cap_drop_fs_set(new->cap_effective);

			if (!uid_eq(old->fsuid, root_uid) && uid_eq(new->fsuid, root_uid))
				new->cap_effective =
					cap_raise_fs_set(new->cap_effective,
							 new->cap_permitted);
		}
		break;

	default:
		return -EINVAL;
	}

	return 0;
}