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
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  mnt_backupgid; int /*<<< orphan*/  mnt_backupuid; } ;

/* Variables and functions */
 int CIFS_MOUNT_CIFS_BACKUPGID ; 
 int CIFS_MOUNT_CIFS_BACKUPUID ; 
 int /*<<< orphan*/  current_fsuid () ; 
 scalar_t__ in_group_p (int /*<<< orphan*/ ) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
backup_cred(struct cifs_sb_info *cifs_sb)
{
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_CIFS_BACKUPUID) {
		if (uid_eq(cifs_sb->mnt_backupuid, current_fsuid()))
			return true;
	}
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_CIFS_BACKUPGID) {
		if (in_group_p(cifs_sb->mnt_backupgid))
			return true;
	}

	return false;
}