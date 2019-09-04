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
struct super_block {int s_blocksize; int s_blocksize_bits; char* s_fs_info; int /*<<< orphan*/ * s_root; int /*<<< orphan*/  s_maxbytes; int /*<<< orphan*/ * s_d_op; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HOSTFS_SUPER_MAGIC ; 
 scalar_t__ IS_ERR (char*) ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int PTR_ERR (char*) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * d_make_root (struct inode*) ; 
 char* follow_link (char*) ; 
 int /*<<< orphan*/  hostfs_sbops ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 struct inode* new_inode (struct super_block*) ; 
 int read_name (struct inode*,char*) ; 
 char* root_ino ; 
 int /*<<< orphan*/  simple_dentry_operations ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int hostfs_fill_sb_common(struct super_block *sb, void *d, int silent)
{
	struct inode *root_inode;
	char *host_root_path, *req_root = d;
	int err;

	sb->s_blocksize = 1024;
	sb->s_blocksize_bits = 10;
	sb->s_magic = HOSTFS_SUPER_MAGIC;
	sb->s_op = &hostfs_sbops;
	sb->s_d_op = &simple_dentry_operations;
	sb->s_maxbytes = MAX_LFS_FILESIZE;

	/* NULL is printed as <NULL> by sprintf: avoid that. */
	if (req_root == NULL)
		req_root = "";

	err = -ENOMEM;
	sb->s_fs_info = host_root_path =
		kmalloc(strlen(root_ino) + strlen(req_root) + 2, GFP_KERNEL);
	if (host_root_path == NULL)
		goto out;

	sprintf(host_root_path, "%s/%s", root_ino, req_root);

	root_inode = new_inode(sb);
	if (!root_inode)
		goto out;

	err = read_name(root_inode, host_root_path);
	if (err)
		goto out_put;

	if (S_ISLNK(root_inode->i_mode)) {
		char *name = follow_link(host_root_path);
		if (IS_ERR(name)) {
			err = PTR_ERR(name);
			goto out_put;
		}
		err = read_name(root_inode, name);
		kfree(name);
		if (err)
			goto out_put;
	}

	err = -ENOMEM;
	sb->s_root = d_make_root(root_inode);
	if (sb->s_root == NULL)
		goto out;

	return 0;

out_put:
	iput(root_inode);
out:
	return err;
}