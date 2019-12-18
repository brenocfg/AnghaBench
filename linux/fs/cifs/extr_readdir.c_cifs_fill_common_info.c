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
struct cifs_sb_info {int mnt_dir_mode; int mnt_file_mode; int mnt_cifs_flags; int /*<<< orphan*/  mnt_gid; int /*<<< orphan*/  mnt_uid; } ;
struct cifs_fattr {int cf_cifsattrs; int cf_mode; scalar_t__ cf_eof; int /*<<< orphan*/  cf_flags; int /*<<< orphan*/  cf_dtype; int /*<<< orphan*/  cf_gid; int /*<<< orphan*/  cf_uid; } ;

/* Variables and functions */
 int ATTR_DIRECTORY ; 
 int ATTR_READONLY ; 
 int ATTR_REPARSE ; 
 int ATTR_SYSTEM ; 
 int /*<<< orphan*/  CIFS_FATTR_NEED_REVAL ; 
 int /*<<< orphan*/  CIFS_FATTR_UNKNOWN_NLINK ; 
 int CIFS_MOUNT_CIFS_ACL ; 
 int CIFS_MOUNT_UNX_EMUL ; 
 int /*<<< orphan*/  DT_DIR ; 
 int /*<<< orphan*/  DT_FIFO ; 
 int /*<<< orphan*/  DT_REG ; 
 int S_IFDIR ; 
 int S_IFIFO ; 
 int S_IFMT ; 
 int S_IFREG ; 
 int S_IWUGO ; 

__attribute__((used)) static void
cifs_fill_common_info(struct cifs_fattr *fattr, struct cifs_sb_info *cifs_sb)
{
	fattr->cf_uid = cifs_sb->mnt_uid;
	fattr->cf_gid = cifs_sb->mnt_gid;

	if (fattr->cf_cifsattrs & ATTR_DIRECTORY) {
		fattr->cf_mode = S_IFDIR | cifs_sb->mnt_dir_mode;
		fattr->cf_dtype = DT_DIR;
	} else {
		fattr->cf_mode = S_IFREG | cifs_sb->mnt_file_mode;
		fattr->cf_dtype = DT_REG;
	}

	/*
	 * We need to revalidate it further to make a decision about whether it
	 * is a symbolic link, DFS referral or a reparse point with a direct
	 * access like junctions, deduplicated files, NFS symlinks.
	 */
	if (fattr->cf_cifsattrs & ATTR_REPARSE)
		fattr->cf_flags |= CIFS_FATTR_NEED_REVAL;

	/* non-unix readdir doesn't provide nlink */
	fattr->cf_flags |= CIFS_FATTR_UNKNOWN_NLINK;

	if (fattr->cf_cifsattrs & ATTR_READONLY)
		fattr->cf_mode &= ~S_IWUGO;

	/*
	 * We of course don't get ACL info in FIND_FIRST/NEXT results, so
	 * mark it for revalidation so that "ls -l" will look right. It might
	 * be super-slow, but if we don't do this then the ownership of files
	 * may look wrong since the inodes may not have timed out by the time
	 * "ls" does a stat() call on them.
	 */
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_CIFS_ACL)
		fattr->cf_flags |= CIFS_FATTR_NEED_REVAL;

	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_UNX_EMUL &&
	    fattr->cf_cifsattrs & ATTR_SYSTEM) {
		if (fattr->cf_eof == 0)  {
			fattr->cf_mode &= ~S_IFMT;
			fattr->cf_mode |= S_IFIFO;
			fattr->cf_dtype = DT_FIFO;
		} else {
			/*
			 * trying to get the type and mode via SFU can be slow,
			 * so just call those regular files for now, and mark
			 * for reval
			 */
			fattr->cf_flags |= CIFS_FATTR_NEED_REVAL;
		}
	}
}