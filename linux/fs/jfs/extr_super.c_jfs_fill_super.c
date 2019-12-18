#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_quota_types; int s_time_gran; scalar_t__ s_blocksize; int /*<<< orphan*/  s_maxbytes; int /*<<< orphan*/  s_root; int /*<<< orphan*/ * s_d_op; int /*<<< orphan*/  s_magic; TYPE_1__* s_bdev; int /*<<< orphan*/ * s_qcop; int /*<<< orphan*/ * dq_op; int /*<<< orphan*/  s_xattr; int /*<<< orphan*/ * s_export_op; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_time_max; scalar_t__ s_time_min; int /*<<< orphan*/  s_max_links; struct jfs_sb_info* s_fs_info; } ;
struct jfs_sb_info {int umask; int flag; int mntflag; int /*<<< orphan*/  nls_tab; struct inode* direct_inode; int /*<<< orphan*/ * log; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; struct super_block* sb; } ;
struct inode {TYPE_2__* i_mapping; int /*<<< orphan*/  i_size; scalar_t__ i_ino; } ;
typedef  scalar_t__ s64 ;
typedef  int loff_t ;
struct TYPE_6__ {int /*<<< orphan*/ * a_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INVALID_GID ; 
 int /*<<< orphan*/  INVALID_UID ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int JFS_ERR_REMOUNT_RO ; 
 int /*<<< orphan*/  JFS_LINK_MAX ; 
 int JFS_OS2 ; 
 int /*<<< orphan*/  JFS_SUPER_MAGIC ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int /*<<< orphan*/  PSIZE ; 
 int PTR_ERR (struct inode*) ; 
 int QTYPE_MASK_GRP ; 
 int QTYPE_MASK_USR ; 
 int /*<<< orphan*/  ROOT_I ; 
 int /*<<< orphan*/  SB_POSIXACL ; 
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 int /*<<< orphan*/  dquot_operations ; 
 int /*<<< orphan*/  filemap_write_and_wait (TYPE_2__*) ; 
 int /*<<< orphan*/  i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_fake_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  jfs_ci_dentry_operations ; 
 int /*<<< orphan*/  jfs_err (char*,...) ; 
 int /*<<< orphan*/  jfs_export_operations ; 
 struct inode* jfs_iget (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_metapage_aops ; 
 int jfs_mount (struct super_block*) ; 
 int jfs_mount_rw (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_quotactl_ops ; 
 int /*<<< orphan*/  jfs_super_operations ; 
 int jfs_umount (struct super_block*) ; 
 int /*<<< orphan*/  jfs_xattr_handlers ; 
 int /*<<< orphan*/  kfree (struct jfs_sb_info*) ; 
 struct jfs_sb_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  parse_options (char*,struct super_block*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  sb_set_blocksize (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_inode_pages (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unload_nls (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jfs_fill_super(struct super_block *sb, void *data, int silent)
{
	struct jfs_sb_info *sbi;
	struct inode *inode;
	int rc;
	s64 newLVSize = 0;
	int flag, ret = -EINVAL;

	jfs_info("In jfs_read_super: s_flags=0x%lx", sb->s_flags);

	sbi = kzalloc(sizeof(struct jfs_sb_info), GFP_KERNEL);
	if (!sbi)
		return -ENOMEM;

	sb->s_fs_info = sbi;
	sb->s_max_links = JFS_LINK_MAX;
	sb->s_time_min = 0;
	sb->s_time_max = U32_MAX;
	sbi->sb = sb;
	sbi->uid = INVALID_UID;
	sbi->gid = INVALID_GID;
	sbi->umask = -1;

	/* initialize the mount flag and determine the default error handler */
	flag = JFS_ERR_REMOUNT_RO;

	if (!parse_options((char *) data, sb, &newLVSize, &flag))
		goto out_kfree;
	sbi->flag = flag;

#ifdef CONFIG_JFS_POSIX_ACL
	sb->s_flags |= SB_POSIXACL;
#endif

	if (newLVSize) {
		pr_err("resize option for remount only\n");
		goto out_kfree;
	}

	/*
	 * Initialize blocksize to 4K.
	 */
	sb_set_blocksize(sb, PSIZE);

	/*
	 * Set method vectors.
	 */
	sb->s_op = &jfs_super_operations;
	sb->s_export_op = &jfs_export_operations;
	sb->s_xattr = jfs_xattr_handlers;
#ifdef CONFIG_QUOTA
	sb->dq_op = &dquot_operations;
	sb->s_qcop = &jfs_quotactl_ops;
	sb->s_quota_types = QTYPE_MASK_USR | QTYPE_MASK_GRP;
#endif

	/*
	 * Initialize direct-mapping inode/address-space
	 */
	inode = new_inode(sb);
	if (inode == NULL) {
		ret = -ENOMEM;
		goto out_unload;
	}
	inode->i_ino = 0;
	inode->i_size = i_size_read(sb->s_bdev->bd_inode);
	inode->i_mapping->a_ops = &jfs_metapage_aops;
	inode_fake_hash(inode);
	mapping_set_gfp_mask(inode->i_mapping, GFP_NOFS);

	sbi->direct_inode = inode;

	rc = jfs_mount(sb);
	if (rc) {
		if (!silent)
			jfs_err("jfs_mount failed w/return code = %d", rc);
		goto out_mount_failed;
	}
	if (sb_rdonly(sb))
		sbi->log = NULL;
	else {
		rc = jfs_mount_rw(sb, 0);
		if (rc) {
			if (!silent) {
				jfs_err("jfs_mount_rw failed, return code = %d",
					rc);
			}
			goto out_no_rw;
		}
	}

	sb->s_magic = JFS_SUPER_MAGIC;

	if (sbi->mntflag & JFS_OS2)
		sb->s_d_op = &jfs_ci_dentry_operations;

	inode = jfs_iget(sb, ROOT_I);
	if (IS_ERR(inode)) {
		ret = PTR_ERR(inode);
		goto out_no_rw;
	}
	sb->s_root = d_make_root(inode);
	if (!sb->s_root)
		goto out_no_root;

	/* logical blocks are represented by 40 bits in pxd_t, etc.
	 * and page cache is indexed by long
	 */
	sb->s_maxbytes = min(((loff_t)sb->s_blocksize) << 40, MAX_LFS_FILESIZE);
	sb->s_time_gran = 1;
	return 0;

out_no_root:
	jfs_err("jfs_read_super: get root dentry failed");

out_no_rw:
	rc = jfs_umount(sb);
	if (rc)
		jfs_err("jfs_umount failed with return code %d", rc);
out_mount_failed:
	filemap_write_and_wait(sbi->direct_inode->i_mapping);
	truncate_inode_pages(sbi->direct_inode->i_mapping, 0);
	make_bad_inode(sbi->direct_inode);
	iput(sbi->direct_inode);
	sbi->direct_inode = NULL;
out_unload:
	unload_nls(sbi->nls_tab);
out_kfree:
	kfree(sbi);
	return ret;
}