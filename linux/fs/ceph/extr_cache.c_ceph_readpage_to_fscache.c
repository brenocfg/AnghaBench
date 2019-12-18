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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct ceph_inode_info {int /*<<< orphan*/  fscache; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PageFsCache (struct page*) ; 
 int /*<<< orphan*/  cache_valid (struct ceph_inode_info*) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  fscache_uncache_page (int /*<<< orphan*/ ,struct page*) ; 
 int fscache_write_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 

void ceph_readpage_to_fscache(struct inode *inode, struct page *page)
{
	struct ceph_inode_info *ci = ceph_inode(inode);
	int ret;

	if (!PageFsCache(page))
		return;

	if (!cache_valid(ci))
		return;

	ret = fscache_write_page(ci->fscache, page, i_size_read(inode),
				 GFP_KERNEL);
	if (ret)
		 fscache_uncache_page(ci->fscache, page);
}