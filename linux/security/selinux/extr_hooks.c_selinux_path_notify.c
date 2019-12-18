#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct path {TYPE_2__* dentry; } ;
struct TYPE_3__ {struct path path; } ;
struct common_audit_data {TYPE_1__ u; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int ALL_FSNOTIFY_PERM_EVENTS ; 
 int EINVAL ; 
 int /*<<< orphan*/  FILESYSTEM__WATCH ; 
 int /*<<< orphan*/  FILE__WATCH ; 
 int /*<<< orphan*/  FILE__WATCH_MOUNT ; 
 int /*<<< orphan*/  FILE__WATCH_READS ; 
 int /*<<< orphan*/  FILE__WATCH_SB ; 
 int /*<<< orphan*/  FILE__WATCH_WITH_PERM ; 
#define  FSNOTIFY_OBJ_TYPE_INODE 130 
#define  FSNOTIFY_OBJ_TYPE_SB 129 
#define  FSNOTIFY_OBJ_TYPE_VFSMOUNT 128 
 int FS_ACCESS ; 
 int FS_ACCESS_PERM ; 
 int FS_CLOSE_NOWRITE ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_PATH ; 
 int /*<<< orphan*/  current_cred () ; 
 int path_has_perm (int /*<<< orphan*/ ,struct path const*,int /*<<< orphan*/ ) ; 
 int superblock_has_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct common_audit_data*) ; 

__attribute__((used)) static int selinux_path_notify(const struct path *path, u64 mask,
						unsigned int obj_type)
{
	int ret;
	u32 perm;

	struct common_audit_data ad;

	ad.type = LSM_AUDIT_DATA_PATH;
	ad.u.path = *path;

	/*
	 * Set permission needed based on the type of mark being set.
	 * Performs an additional check for sb watches.
	 */
	switch (obj_type) {
	case FSNOTIFY_OBJ_TYPE_VFSMOUNT:
		perm = FILE__WATCH_MOUNT;
		break;
	case FSNOTIFY_OBJ_TYPE_SB:
		perm = FILE__WATCH_SB;
		ret = superblock_has_perm(current_cred(), path->dentry->d_sb,
						FILESYSTEM__WATCH, &ad);
		if (ret)
			return ret;
		break;
	case FSNOTIFY_OBJ_TYPE_INODE:
		perm = FILE__WATCH;
		break;
	default:
		return -EINVAL;
	}

	/* blocking watches require the file:watch_with_perm permission */
	if (mask & (ALL_FSNOTIFY_PERM_EVENTS))
		perm |= FILE__WATCH_WITH_PERM;

	/* watches on read-like events need the file:watch_reads permission */
	if (mask & (FS_ACCESS | FS_ACCESS_PERM | FS_CLOSE_NOWRITE))
		perm |= FILE__WATCH_READS;

	return path_has_perm(current_cred(), path, perm);
}