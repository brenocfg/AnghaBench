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
struct super_block {int s_blocksize; int s_blocksize_bits; int s_time_gran; int /*<<< orphan*/ * s_root; int /*<<< orphan*/  s_fs_info; int /*<<< orphan*/ * s_d_op; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_iflags; } ;
struct inode {int i_ino; int i_mode; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; } ;
struct TYPE_2__ {int /*<<< orphan*/  mount_opts; } ;

/* Variables and functions */
 TYPE_1__* DEVPTS_SB (struct super_block*) ; 
 int /*<<< orphan*/  DEVPTS_SUPER_MAGIC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PARSE_MOUNT ; 
 int /*<<< orphan*/  SB_I_NODEV ; 
 int S_IFDIR ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 int S_IXUGO ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/ * d_make_root (struct inode*) ; 
 int /*<<< orphan*/  devpts_sops ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ *) ; 
 int mknod_ptmx (struct super_block*) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  new_pts_fs_info (struct super_block*) ; 
 int parse_mount_options (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 
 int /*<<< orphan*/  simple_dentry_operations ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 
 int /*<<< orphan*/  simple_dir_operations ; 

__attribute__((used)) static int
devpts_fill_super(struct super_block *s, void *data, int silent)
{
	struct inode *inode;
	int error;

	s->s_iflags &= ~SB_I_NODEV;
	s->s_blocksize = 1024;
	s->s_blocksize_bits = 10;
	s->s_magic = DEVPTS_SUPER_MAGIC;
	s->s_op = &devpts_sops;
	s->s_d_op = &simple_dentry_operations;
	s->s_time_gran = 1;

	error = -ENOMEM;
	s->s_fs_info = new_pts_fs_info(s);
	if (!s->s_fs_info)
		goto fail;

	error = parse_mount_options(data, PARSE_MOUNT, &DEVPTS_SB(s)->mount_opts);
	if (error)
		goto fail;

	error = -ENOMEM;
	inode = new_inode(s);
	if (!inode)
		goto fail;
	inode->i_ino = 1;
	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);
	inode->i_mode = S_IFDIR | S_IRUGO | S_IXUGO | S_IWUSR;
	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;
	set_nlink(inode, 2);

	s->s_root = d_make_root(inode);
	if (!s->s_root) {
		pr_err("get root dentry failed\n");
		goto fail;
	}

	error = mknod_ptmx(s);
	if (error)
		goto fail_dput;

	return 0;
fail_dput:
	dput(s->s_root);
	s->s_root = NULL;
fail:
	return error;
}