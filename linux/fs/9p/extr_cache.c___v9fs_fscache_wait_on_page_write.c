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
struct v9fs_inode {int /*<<< orphan*/  fscache; } ;
struct page {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_FSC ; 
 scalar_t__ PageFsCache (struct page*) ; 
 struct v9fs_inode* V9FS_I (struct inode*) ; 
 int /*<<< orphan*/  fscache_wait_on_page_write (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct inode*,struct page*) ; 

void __v9fs_fscache_wait_on_page_write(struct inode *inode, struct page *page)
{
	const struct v9fs_inode *v9inode = V9FS_I(inode);
	p9_debug(P9_DEBUG_FSC, "inode %p page %p\n", inode, page);
	if (PageFsCache(page))
		fscache_wait_on_page_write(v9inode->fscache, page);
}