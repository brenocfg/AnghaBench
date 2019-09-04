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
struct dentry {int dummy; } ;
struct cpu_vfs_cap_data {int magic_etc; int /*<<< orphan*/  inheritable; int /*<<< orphan*/  permitted; } ;
struct TYPE_2__ {int fE; int /*<<< orphan*/  inheritable; int /*<<< orphan*/  permitted; } ;
struct audit_names {int fcap_ver; TYPE_1__ fcap; } ;

/* Variables and functions */
 int VFS_CAP_FLAGS_EFFECTIVE ; 
 int VFS_CAP_REVISION_MASK ; 
 int VFS_CAP_REVISION_SHIFT ; 
 int get_vfs_caps_from_disk (struct dentry const*,struct cpu_vfs_cap_data*) ; 

__attribute__((used)) static inline int audit_copy_fcaps(struct audit_names *name,
				   const struct dentry *dentry)
{
	struct cpu_vfs_cap_data caps;
	int rc;

	if (!dentry)
		return 0;

	rc = get_vfs_caps_from_disk(dentry, &caps);
	if (rc)
		return rc;

	name->fcap.permitted = caps.permitted;
	name->fcap.inheritable = caps.inheritable;
	name->fcap.fE = !!(caps.magic_etc & VFS_CAP_FLAGS_EFFECTIVE);
	name->fcap_ver = (caps.magic_etc & VFS_CAP_REVISION_MASK) >>
				VFS_CAP_REVISION_SHIFT;

	return 0;
}