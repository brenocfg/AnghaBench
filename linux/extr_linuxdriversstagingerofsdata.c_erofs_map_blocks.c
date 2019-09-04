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
struct erofs_map_blocks {int dummy; } ;

/* Variables and functions */
 int erofs_map_blocks_flatmode (struct inode*,struct erofs_map_blocks*,int) ; 
 int erofs_map_blocks_iter (struct inode*,struct erofs_map_blocks*,struct page**,int) ; 
 int /*<<< orphan*/  is_inode_layout_compression (struct inode*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int erofs_map_blocks(struct inode *inode,
	struct erofs_map_blocks *map, int flags)
{
	if (unlikely(is_inode_layout_compression(inode))) {
		struct page *mpage = NULL;
		int err;

		err = erofs_map_blocks_iter(inode, map, &mpage, flags);
		if (mpage != NULL)
			put_page(mpage);
		return err;
	}
	return erofs_map_blocks_flatmode(inode, map, flags);
}