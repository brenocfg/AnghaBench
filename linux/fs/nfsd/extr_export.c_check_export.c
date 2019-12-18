#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_3__* i_sb; int /*<<< orphan*/  i_mode; } ;
struct TYPE_6__ {TYPE_2__* s_export_op; TYPE_1__* s_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  fh_to_dentry; } ;
struct TYPE_4__ {int fs_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTDIR ; 
 int FS_REQUIRES_DEV ; 
 int NFSEXP_FSID ; 
 int NFSEXP_READONLY ; 
 int NFSEXP_V4ROOT ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static int check_export(struct inode *inode, int *flags, unsigned char *uuid)
{

	/*
	 * We currently export only dirs, regular files, and (for v4
	 * pseudoroot) symlinks.
	 */
	if (!S_ISDIR(inode->i_mode) &&
	    !S_ISLNK(inode->i_mode) &&
	    !S_ISREG(inode->i_mode))
		return -ENOTDIR;

	/*
	 * Mountd should never pass down a writeable V4ROOT export, but,
	 * just to make sure:
	 */
	if (*flags & NFSEXP_V4ROOT)
		*flags |= NFSEXP_READONLY;

	/* There are two requirements on a filesystem to be exportable.
	 * 1:  We must be able to identify the filesystem from a number.
	 *       either a device number (so FS_REQUIRES_DEV needed)
	 *       or an FSID number (so NFSEXP_FSID or ->uuid is needed).
	 * 2:  We must be able to find an inode from a filehandle.
	 *       This means that s_export_op must be set.
	 */
	if (!(inode->i_sb->s_type->fs_flags & FS_REQUIRES_DEV) &&
	    !(*flags & NFSEXP_FSID) &&
	    uuid == NULL) {
		dprintk("exp_export: export of non-dev fs without fsid\n");
		return -EINVAL;
	}

	if (!inode->i_sb->s_export_op ||
	    !inode->i_sb->s_export_op->fh_to_dentry) {
		dprintk("exp_export: export of invalid fs type.\n");
		return -EINVAL;
	}

	return 0;

}