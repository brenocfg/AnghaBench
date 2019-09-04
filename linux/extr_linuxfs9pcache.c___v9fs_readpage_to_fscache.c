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
struct v9fs_inode {int /*<<< orphan*/  vfs_inode; int /*<<< orphan*/  fscache; } ;
struct page {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  P9_DEBUG_FSC ; 
 struct v9fs_inode* V9FS_I (struct inode*) ; 
 int fscache_write_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  v9fs_uncache_page (struct inode*,struct page*) ; 

void __v9fs_readpage_to_fscache(struct inode *inode, struct page *page)
{
	int ret;
	const struct v9fs_inode *v9inode = V9FS_I(inode);

	p9_debug(P9_DEBUG_FSC, "inode %p page %p\n", inode, page);
	ret = fscache_write_page(v9inode->fscache, page,
				 i_size_read(&v9inode->vfs_inode), GFP_KERNEL);
	p9_debug(P9_DEBUG_FSC, "ret =  %d\n", ret);
	if (ret != 0)
		v9fs_uncache_page(inode, page);
}