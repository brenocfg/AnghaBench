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
 int ENOTSUPP ; 
 int erofs_map_blocks (struct inode*,struct erofs_map_blocks*,int) ; 
 int /*<<< orphan*/  is_inode_layout_compression (struct inode*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 

int erofs_map_blocks_iter(struct inode *inode,
	struct erofs_map_blocks *map,
	struct page **mpage_ret, int flags)
{
	/* by default, reading raw data never use erofs_map_blocks_iter */
	if (unlikely(!is_inode_layout_compression(inode))) {
		if (*mpage_ret != NULL)
			put_page(*mpage_ret);
		*mpage_ret = NULL;

		return erofs_map_blocks(inode, map, flags);
	}

#ifdef CONFIG_EROFS_FS_ZIP
	return z_erofs_map_blocks_iter(inode, map, mpage_ret, flags);
#else
	/* data compression is not available */
	return -ENOTSUPP;
#endif
}