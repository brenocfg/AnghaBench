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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {struct ceph_file_info* private_data; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_cap_wq; } ;
struct TYPE_2__ {int /*<<< orphan*/  fmode; int /*<<< orphan*/  rw_contexts; } ;
struct ceph_file_info {int /*<<< orphan*/  fmode; int /*<<< orphan*/  rw_contexts; int /*<<< orphan*/  dir_info; int /*<<< orphan*/  last_name; scalar_t__ last_readdir; TYPE_1__ file_info; } ;
struct ceph_dir_file_info {int /*<<< orphan*/  fmode; int /*<<< orphan*/  rw_contexts; int /*<<< orphan*/  dir_info; int /*<<< orphan*/  last_name; scalar_t__ last_readdir; TYPE_1__ file_info; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ceph_dir_file_cachep ; 
 int /*<<< orphan*/  ceph_file_cachep ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  ceph_mdsc_put_request (scalar_t__) ; 
 int /*<<< orphan*/  ceph_put_fmode (struct ceph_inode_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,struct file*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ceph_file_info*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

int ceph_release(struct inode *inode, struct file *file)
{
	struct ceph_inode_info *ci = ceph_inode(inode);

	if (S_ISDIR(inode->i_mode)) {
		struct ceph_dir_file_info *dfi = file->private_data;
		dout("release inode %p dir file %p\n", inode, file);
		WARN_ON(!list_empty(&dfi->file_info.rw_contexts));

		ceph_put_fmode(ci, dfi->file_info.fmode);

		if (dfi->last_readdir)
			ceph_mdsc_put_request(dfi->last_readdir);
		kfree(dfi->last_name);
		kfree(dfi->dir_info);
		kmem_cache_free(ceph_dir_file_cachep, dfi);
	} else {
		struct ceph_file_info *fi = file->private_data;
		dout("release inode %p regular file %p\n", inode, file);
		WARN_ON(!list_empty(&fi->rw_contexts));

		ceph_put_fmode(ci, fi->fmode);
		kmem_cache_free(ceph_file_cachep, fi);
	}

	/* wake up anyone waiting for caps on this inode */
	wake_up_all(&ci->i_cap_wq);
	return 0;
}