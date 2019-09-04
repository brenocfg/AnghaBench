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
struct xattr_handler {int dummy; } ;
struct super_operations {int dummy; } ;
struct super_block {unsigned long s_magic; int s_time_gran; struct dentry* s_root; int /*<<< orphan*/  s_flags; struct dentry_operations const* s_d_op; struct xattr_handler const** s_xattr; struct super_operations const* s_op; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_maxbytes; } ;
struct qstr {int dummy; } ;
struct inode {int i_ino; int i_mode; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; } ;
struct file_system_type {int dummy; } ;
struct dentry_operations {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_CAST (struct super_block*) ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct qstr QSTR_INIT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_ACTIVE ; 
 int SB_KERNMOUNT ; 
 int SB_NOUSER ; 
 int S_IFDIR ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 struct dentry* __d_alloc (struct super_block*,struct qstr*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 struct dentry* dget (struct dentry*) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  set_anon_super ; 
 struct super_block* sget_userns (struct file_system_type*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct super_operations const simple_super_operations ; 
 int /*<<< orphan*/  strlen (char*) ; 

struct dentry *mount_pseudo_xattr(struct file_system_type *fs_type, char *name,
	const struct super_operations *ops, const struct xattr_handler **xattr,
	const struct dentry_operations *dops, unsigned long magic)
{
	struct super_block *s;
	struct dentry *dentry;
	struct inode *root;
	struct qstr d_name = QSTR_INIT(name, strlen(name));

	s = sget_userns(fs_type, NULL, set_anon_super, SB_KERNMOUNT|SB_NOUSER,
			&init_user_ns, NULL);
	if (IS_ERR(s))
		return ERR_CAST(s);

	s->s_maxbytes = MAX_LFS_FILESIZE;
	s->s_blocksize = PAGE_SIZE;
	s->s_blocksize_bits = PAGE_SHIFT;
	s->s_magic = magic;
	s->s_op = ops ? ops : &simple_super_operations;
	s->s_xattr = xattr;
	s->s_time_gran = 1;
	root = new_inode(s);
	if (!root)
		goto Enomem;
	/*
	 * since this is the first inode, make it number 1. New inodes created
	 * after this must take care not to collide with it (by passing
	 * max_reserved of 1 to iunique).
	 */
	root->i_ino = 1;
	root->i_mode = S_IFDIR | S_IRUSR | S_IWUSR;
	root->i_atime = root->i_mtime = root->i_ctime = current_time(root);
	dentry = __d_alloc(s, &d_name);
	if (!dentry) {
		iput(root);
		goto Enomem;
	}
	d_instantiate(dentry, root);
	s->s_root = dentry;
	s->s_d_op = dops;
	s->s_flags |= SB_ACTIVE;
	return dget(s->s_root);

Enomem:
	deactivate_locked_super(s);
	return ERR_PTR(-ENOMEM);
}