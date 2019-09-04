#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * a_ops; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_rdev; int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; TYPE_3__ i_data; int /*<<< orphan*/  i_sb; } ;
struct cifs_sb_info {int mnt_cifs_flags; } ;
struct TYPE_8__ {TYPE_2__* ses; } ;
struct TYPE_6__ {TYPE_1__* server; } ;
struct TYPE_5__ {scalar_t__ maxBuf; } ;

/* Variables and functions */
 int CIFS_MOUNT_DIRECT_IO ; 
 int CIFS_MOUNT_NO_BRL ; 
 int CIFS_MOUNT_STRICT_IO ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_CIFS_HDR_SIZE ; 
 scalar_t__ PAGE_SIZE ; 
#define  S_IFDIR 130 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int /*<<< orphan*/  cifs_addr_ops ; 
 int /*<<< orphan*/  cifs_addr_ops_smallbuf ; 
 int /*<<< orphan*/  cifs_dir_inode_ops ; 
 int /*<<< orphan*/  cifs_dir_ops ; 
 int /*<<< orphan*/  cifs_file_direct_nobrl_ops ; 
 int /*<<< orphan*/  cifs_file_direct_ops ; 
 int /*<<< orphan*/  cifs_file_inode_ops ; 
 int /*<<< orphan*/  cifs_file_nobrl_ops ; 
 int /*<<< orphan*/  cifs_file_ops ; 
 int /*<<< orphan*/  cifs_file_strict_nobrl_ops ; 
 int /*<<< orphan*/  cifs_file_strict_ops ; 
 TYPE_4__* cifs_sb_master_tcon (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_symlink_inode_ops ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cifs_set_ops(struct inode *inode)
{
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);

	switch (inode->i_mode & S_IFMT) {
	case S_IFREG:
		inode->i_op = &cifs_file_inode_ops;
		if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_DIRECT_IO) {
			if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NO_BRL)
				inode->i_fop = &cifs_file_direct_nobrl_ops;
			else
				inode->i_fop = &cifs_file_direct_ops;
		} else if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_STRICT_IO) {
			if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NO_BRL)
				inode->i_fop = &cifs_file_strict_nobrl_ops;
			else
				inode->i_fop = &cifs_file_strict_ops;
		} else if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NO_BRL)
			inode->i_fop = &cifs_file_nobrl_ops;
		else { /* not direct, send byte range locks */
			inode->i_fop = &cifs_file_ops;
		}

		/* check if server can support readpages */
		if (cifs_sb_master_tcon(cifs_sb)->ses->server->maxBuf <
				PAGE_SIZE + MAX_CIFS_HDR_SIZE)
			inode->i_data.a_ops = &cifs_addr_ops_smallbuf;
		else
			inode->i_data.a_ops = &cifs_addr_ops;
		break;
	case S_IFDIR:
#ifdef CONFIG_CIFS_DFS_UPCALL
		if (IS_AUTOMOUNT(inode)) {
			inode->i_op = &cifs_dfs_referral_inode_operations;
		} else {
#else /* NO DFS support, treat as a directory */
		{
#endif
			inode->i_op = &cifs_dir_inode_ops;
			inode->i_fop = &cifs_dir_ops;
		}
		break;
	case S_IFLNK:
		inode->i_op = &cifs_symlink_inode_ops;
		break;
	default:
		init_special_inode(inode, inode->i_mode, inode->i_rdev);
		break;
	}
}