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
typedef  int umode_t ;
struct inode_operations {int dummy; } ;
struct inode {int dummy; } ;
struct file_operations {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int EEXIST ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int S_IALLUGO ; 
 int S_IFMT ; 
 int S_IFREG ; 
 int __aafs_setup_d_inode (struct inode*,struct dentry*,int,void*,void*,struct file_operations const*,struct inode_operations const*) ; 
 int /*<<< orphan*/  aafs_count ; 
 int /*<<< orphan*/  aafs_mnt ; 
 int /*<<< orphan*/  aafs_ops ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 struct dentry* lookup_one_len (char const*,struct dentry*,int /*<<< orphan*/ ) ; 
 int simple_pin_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_release_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static struct dentry *aafs_create(const char *name, umode_t mode,
				  struct dentry *parent, void *data, void *link,
				  const struct file_operations *fops,
				  const struct inode_operations *iops)
{
	struct dentry *dentry;
	struct inode *dir;
	int error;

	AA_BUG(!name);
	AA_BUG(!parent);

	if (!(mode & S_IFMT))
		mode = (mode & S_IALLUGO) | S_IFREG;

	error = simple_pin_fs(&aafs_ops, &aafs_mnt, &aafs_count);
	if (error)
		return ERR_PTR(error);

	dir = d_inode(parent);

	inode_lock(dir);
	dentry = lookup_one_len(name, parent, strlen(name));
	if (IS_ERR(dentry)) {
		error = PTR_ERR(dentry);
		goto fail_lock;
	}

	if (d_really_is_positive(dentry)) {
		error = -EEXIST;
		goto fail_dentry;
	}

	error = __aafs_setup_d_inode(dir, dentry, mode, data, link, fops, iops);
	if (error)
		goto fail_dentry;
	inode_unlock(dir);

	return dentry;

fail_dentry:
	dput(dentry);

fail_lock:
	inode_unlock(dir);
	simple_release_fs(&aafs_mnt, &aafs_count);

	return ERR_PTR(error);
}