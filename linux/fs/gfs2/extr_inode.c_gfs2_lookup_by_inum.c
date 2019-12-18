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
typedef  scalar_t__ u64 ;
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct gfs2_sbd {struct super_block* sd_vfs; } ;
struct TYPE_2__ {scalar_t__ i_no_formal_ino; int i_diskflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_UNKNOWN ; 
 int EIO ; 
 struct inode* ERR_PTR (int) ; 
 int ESTALE ; 
 int GFS2_DIF_SYSTEM ; 
 TYPE_1__* GFS2_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct inode* gfs2_inode_lookup (struct super_block*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

struct inode *gfs2_lookup_by_inum(struct gfs2_sbd *sdp, u64 no_addr,
				  u64 *no_formal_ino, unsigned int blktype)
{
	struct super_block *sb = sdp->sd_vfs;
	struct inode *inode;
	int error;

	inode = gfs2_inode_lookup(sb, DT_UNKNOWN, no_addr, 0, blktype);
	if (IS_ERR(inode))
		return inode;

	/* Two extra checks for NFS only */
	if (no_formal_ino) {
		error = -ESTALE;
		if (GFS2_I(inode)->i_no_formal_ino != *no_formal_ino)
			goto fail_iput;

		error = -EIO;
		if (GFS2_I(inode)->i_diskflags & GFS2_DIF_SYSTEM)
			goto fail_iput;
	}
	return inode;

fail_iput:
	iput(inode);
	return ERR_PTR(error);
}