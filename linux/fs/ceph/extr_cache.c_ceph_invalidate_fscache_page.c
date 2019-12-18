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
 int /*<<< orphan*/  PageFsCache (struct page*) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  fscache_uncache_page (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  fscache_wait_on_page_write (int /*<<< orphan*/ ,struct page*) ; 

void ceph_invalidate_fscache_page(struct inode* inode, struct page *page)
{
	struct ceph_inode_info *ci = ceph_inode(inode);

	if (!PageFsCache(page))
		return;

	fscache_wait_on_page_write(ci->fscache, page);
	fscache_uncache_page(ci->fscache, page);
}