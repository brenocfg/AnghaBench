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
typedef  int /*<<< orphan*/  u64 ;
struct super_block {struct gfs2_sbd* s_fs_info; } ;
struct inode {int dummy; } ;
struct gfs2_sbd {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_DIR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFS2_BLKST_FREE ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 struct dentry* d_make_root (struct inode*) ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,char const*,...) ; 
 struct inode* gfs2_inode_lookup (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfs2_lookup_root(struct super_block *sb, struct dentry **dptr,
			    u64 no_addr, const char *name)
{
	struct gfs2_sbd *sdp = sb->s_fs_info;
	struct dentry *dentry;
	struct inode *inode;

	inode = gfs2_inode_lookup(sb, DT_DIR, no_addr, 0,
				  GFS2_BLKST_FREE /* ignore */);
	if (IS_ERR(inode)) {
		fs_err(sdp, "can't read in %s inode: %ld\n", name, PTR_ERR(inode));
		return PTR_ERR(inode);
	}
	dentry = d_make_root(inode);
	if (!dentry) {
		fs_err(sdp, "can't alloc %s dentry\n", name);
		return -ENOMEM;
	}
	*dptr = dentry;
	return 0;
}