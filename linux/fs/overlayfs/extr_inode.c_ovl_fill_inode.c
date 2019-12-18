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
typedef  int umode_t ;
struct inode {unsigned long i_ino; int i_mode; int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; TYPE_1__* i_mapping; int /*<<< orphan*/  i_default_acl; int /*<<< orphan*/  i_acl; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_DONT_CACHE ; 
#define  S_IFDIR 130 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int /*<<< orphan*/  S_NOCMTIME ; 
 unsigned long get_next_ino () ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_aops ; 
 int /*<<< orphan*/  ovl_dir_inode_operations ; 
 int /*<<< orphan*/  ovl_dir_operations ; 
 int /*<<< orphan*/  ovl_file_inode_operations ; 
 int /*<<< orphan*/  ovl_file_operations ; 
 int /*<<< orphan*/  ovl_lockdep_annotate_inode_mutex_key (struct inode*) ; 
 scalar_t__ ovl_same_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_special_inode_operations ; 
 int /*<<< orphan*/  ovl_symlink_inode_operations ; 
 int ovl_xino_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ovl_fill_inode(struct inode *inode, umode_t mode, dev_t rdev,
			   unsigned long ino, int fsid)
{
	int xinobits = ovl_xino_bits(inode->i_sb);

	/*
	 * When d_ino is consistent with st_ino (samefs or i_ino has enough
	 * bits to encode layer), set the same value used for st_ino to i_ino,
	 * so inode number exposed via /proc/locks and a like will be
	 * consistent with d_ino and st_ino values. An i_ino value inconsistent
	 * with d_ino also causes nfsd readdirplus to fail.  When called from
	 * ovl_new_inode(), ino arg is 0, so i_ino will be updated to real
	 * upper inode i_ino on ovl_inode_init() or ovl_inode_update().
	 */
	if (ovl_same_sb(inode->i_sb) || xinobits) {
		inode->i_ino = ino;
		if (xinobits && fsid && !(ino >> (64 - xinobits)))
			inode->i_ino |= (unsigned long)fsid << (64 - xinobits);
	} else {
		inode->i_ino = get_next_ino();
	}
	inode->i_mode = mode;
	inode->i_flags |= S_NOCMTIME;
#ifdef CONFIG_FS_POSIX_ACL
	inode->i_acl = inode->i_default_acl = ACL_DONT_CACHE;
#endif

	ovl_lockdep_annotate_inode_mutex_key(inode);

	switch (mode & S_IFMT) {
	case S_IFREG:
		inode->i_op = &ovl_file_inode_operations;
		inode->i_fop = &ovl_file_operations;
		inode->i_mapping->a_ops = &ovl_aops;
		break;

	case S_IFDIR:
		inode->i_op = &ovl_dir_inode_operations;
		inode->i_fop = &ovl_dir_operations;
		break;

	case S_IFLNK:
		inode->i_op = &ovl_symlink_inode_operations;
		break;

	default:
		inode->i_op = &ovl_special_inode_operations;
		init_special_inode(inode, mode, rdev);
		break;
	}
}