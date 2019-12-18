#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct ceph_file_info* private_data; } ;
struct ceph_rw_context {int dummy; } ;
struct ceph_fs_client {TYPE_1__* mount_options; } ;
struct ceph_file_info {int dummy; } ;
struct address_space {int /*<<< orphan*/  host; } ;
struct TYPE_4__ {scalar_t__ i_inline_version; } ;
struct TYPE_3__ {int rsize; } ;

/* Variables and functions */
 scalar_t__ CEPH_INLINE_NONE ; 
 int EINVAL ; 
 int PAGE_SHIFT ; 
 struct ceph_rw_context* ceph_find_rw_context (struct ceph_file_info*) ; 
 int /*<<< orphan*/  ceph_fscache_readpages_cancel (struct inode*,struct list_head*) ; 
 TYPE_2__* ceph_inode (struct inode*) ; 
 struct ceph_fs_client* ceph_inode_to_client (struct inode*) ; 
 int ceph_readpages_from_fscache (int /*<<< orphan*/ ,struct address_space*,struct list_head*,unsigned int*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,struct file*,int,...) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int start_read (struct inode*,struct ceph_rw_context*,struct list_head*,int) ; 

__attribute__((used)) static int ceph_readpages(struct file *file, struct address_space *mapping,
			  struct list_head *page_list, unsigned nr_pages)
{
	struct inode *inode = file_inode(file);
	struct ceph_fs_client *fsc = ceph_inode_to_client(inode);
	struct ceph_file_info *fi = file->private_data;
	struct ceph_rw_context *rw_ctx;
	int rc = 0;
	int max = 0;

	if (ceph_inode(inode)->i_inline_version != CEPH_INLINE_NONE)
		return -EINVAL;

	rc = ceph_readpages_from_fscache(mapping->host, mapping, page_list,
					 &nr_pages);

	if (rc == 0)
		goto out;

	rw_ctx = ceph_find_rw_context(fi);
	max = fsc->mount_options->rsize >> PAGE_SHIFT;
	dout("readpages %p file %p ctx %p nr_pages %d max %d\n",
	     inode, file, rw_ctx, nr_pages, max);
	while (!list_empty(page_list)) {
		rc = start_read(inode, rw_ctx, page_list, max);
		if (rc < 0)
			goto out;
	}
out:
	ceph_fscache_readpages_cancel(inode, page_list);

	dout("readpages %p file %p ret %d\n", inode, file, rc);
	return rc;
}