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
typedef  int /*<<< orphan*/  u32 ;
struct user_namespace {int flags; int /*<<< orphan*/  parent; int /*<<< orphan*/  owner; } ;
struct uid_gid_map {int nr_extents; TYPE_1__* extent; } ;
struct file {struct cred* f_cred; } ;
struct cred {int /*<<< orphan*/  egid; int /*<<< orphan*/  euid; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
struct TYPE_2__ {int count; int /*<<< orphan*/  lower_first; } ;

/* Variables and functions */
 int CAP_SETGID ; 
 int CAP_SETUID ; 
 int USERNS_SETGROUPS_ALLOWED ; 
 int /*<<< orphan*/  cap_valid (int) ; 
 scalar_t__ file_ns_capable (struct file const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ns_capable (int /*<<< orphan*/ ,int) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool new_idmap_permitted(const struct file *file,
				struct user_namespace *ns, int cap_setid,
				struct uid_gid_map *new_map)
{
	const struct cred *cred = file->f_cred;
	/* Don't allow mappings that would allow anything that wouldn't
	 * be allowed without the establishment of unprivileged mappings.
	 */
	if ((new_map->nr_extents == 1) && (new_map->extent[0].count == 1) &&
	    uid_eq(ns->owner, cred->euid)) {
		u32 id = new_map->extent[0].lower_first;
		if (cap_setid == CAP_SETUID) {
			kuid_t uid = make_kuid(ns->parent, id);
			if (uid_eq(uid, cred->euid))
				return true;
		} else if (cap_setid == CAP_SETGID) {
			kgid_t gid = make_kgid(ns->parent, id);
			if (!(ns->flags & USERNS_SETGROUPS_ALLOWED) &&
			    gid_eq(gid, cred->egid))
				return true;
		}
	}

	/* Allow anyone to set a mapping that doesn't require privilege */
	if (!cap_valid(cap_setid))
		return true;

	/* Allow the specified ids if we have the appropriate capability
	 * (CAP_SETUID or CAP_SETGID) over the parent user namespace.
	 * And the opener of the id file also had the approprpiate capability.
	 */
	if (ns_capable(ns->parent, cap_setid) &&
	    file_ns_capable(file, ns->parent, cap_setid))
		return true;

	return false;
}