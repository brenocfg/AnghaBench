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
struct cred {int /*<<< orphan*/  cap_permitted; int /*<<< orphan*/  cap_effective; int /*<<< orphan*/  euid; int /*<<< orphan*/  cap_ambient; int /*<<< orphan*/  suid; int /*<<< orphan*/  uid; int /*<<< orphan*/  user_ns; } ;
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SECURE_KEEP_CAPS ; 
 int /*<<< orphan*/  cap_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  issecure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cap_emulate_setxuid(struct cred *new, const struct cred *old)
{
	kuid_t root_uid = make_kuid(old->user_ns, 0);

	if ((uid_eq(old->uid, root_uid) ||
	     uid_eq(old->euid, root_uid) ||
	     uid_eq(old->suid, root_uid)) &&
	    (!uid_eq(new->uid, root_uid) &&
	     !uid_eq(new->euid, root_uid) &&
	     !uid_eq(new->suid, root_uid))) {
		if (!issecure(SECURE_KEEP_CAPS)) {
			cap_clear(new->cap_permitted);
			cap_clear(new->cap_effective);
		}

		/*
		 * Pre-ambient programs expect setresuid to nonroot followed
		 * by exec to drop capabilities.  We should make sure that
		 * this remains the case.
		 */
		cap_clear(new->cap_ambient);
	}
	if (uid_eq(old->euid, root_uid) && !uid_eq(new->euid, root_uid))
		cap_clear(new->cap_effective);
	if (!uid_eq(old->euid, root_uid) && uid_eq(new->euid, root_uid))
		new->cap_effective = new->cap_permitted;
}