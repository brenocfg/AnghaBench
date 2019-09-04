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
struct vfsmount {int dummy; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_ino; } ;
struct dentry {TYPE_2__* d_inode; TYPE_1__* d_sb; } ;
struct TYPE_6__ {int /*<<< orphan*/  mnt; int /*<<< orphan*/  dentry; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_type; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  MEM_MAJOR ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NULL_FILE_NAME ; 
 int PTR_ERR (struct dentry*) ; 
 int S_IFCHR ; 
 int S_IRUGO ; 
 int S_IWUGO ; 
 TYPE_3__ aa_null ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  get_next_ino () ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 struct dentry* lookup_one_len (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mntget (struct vfsmount*) ; 
 struct inode* new_inode (int /*<<< orphan*/ ) ; 
 int simple_pin_fs (int /*<<< orphan*/ ,struct vfsmount**,int*) ; 
 int /*<<< orphan*/  simple_release_fs (struct vfsmount**,int*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aa_mk_null_file(struct dentry *parent)
{
	struct vfsmount *mount = NULL;
	struct dentry *dentry;
	struct inode *inode;
	int count = 0;
	int error = simple_pin_fs(parent->d_sb->s_type, &mount, &count);

	if (error)
		return error;

	inode_lock(d_inode(parent));
	dentry = lookup_one_len(NULL_FILE_NAME, parent, strlen(NULL_FILE_NAME));
	if (IS_ERR(dentry)) {
		error = PTR_ERR(dentry);
		goto out;
	}
	inode = new_inode(parent->d_inode->i_sb);
	if (!inode) {
		error = -ENOMEM;
		goto out1;
	}

	inode->i_ino = get_next_ino();
	inode->i_mode = S_IFCHR | S_IRUGO | S_IWUGO;
	inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);
	init_special_inode(inode, S_IFCHR | S_IRUGO | S_IWUGO,
			   MKDEV(MEM_MAJOR, 3));
	d_instantiate(dentry, inode);
	aa_null.dentry = dget(dentry);
	aa_null.mnt = mntget(mount);

	error = 0;

out1:
	dput(dentry);
out:
	inode_unlock(d_inode(parent));
	simple_release_fs(&mount, &count);
	return error;
}