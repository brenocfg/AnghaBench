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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/ * vm_ops; } ;
struct v9fs_inode {int /*<<< orphan*/  v_mutex; void* writeback_fid; } ;
struct p9_fid {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int PTR_ERR (struct p9_fid*) ; 
 struct v9fs_inode* V9FS_I (struct inode*) ; 
 int VM_SHARED ; 
 int VM_WRITE ; 
 int /*<<< orphan*/  file_dentry (struct file*) ; 
 struct inode* file_inode (struct file*) ; 
 int generic_file_mmap (struct file*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v9fs_mmap_file_vm_ops ; 
 struct p9_fid* v9fs_writeback_fid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
v9fs_mmap_file_mmap(struct file *filp, struct vm_area_struct *vma)
{
	int retval;
	struct inode *inode;
	struct v9fs_inode *v9inode;
	struct p9_fid *fid;

	inode = file_inode(filp);
	v9inode = V9FS_I(inode);
	mutex_lock(&v9inode->v_mutex);
	if (!v9inode->writeback_fid &&
	    (vma->vm_flags & VM_SHARED) &&
	    (vma->vm_flags & VM_WRITE)) {
		/*
		 * clone a fid and add it to writeback_fid
		 * we do it during mmap instead of
		 * page dirty time via write_begin/page_mkwrite
		 * because we want write after unlink usecase
		 * to work.
		 */
		fid = v9fs_writeback_fid(file_dentry(filp));
		if (IS_ERR(fid)) {
			retval = PTR_ERR(fid);
			mutex_unlock(&v9inode->v_mutex);
			return retval;
		}
		v9inode->writeback_fid = (void *) fid;
	}
	mutex_unlock(&v9inode->v_mutex);

	retval = generic_file_mmap(filp, vma);
	if (!retval)
		vma->vm_ops = &v9fs_mmap_file_vm_ops;

	return retval;
}