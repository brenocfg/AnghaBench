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
struct nilfs_bmap {TYPE_1__* b_inode; } ;
typedef  struct buffer_head {struct buffer_head const* b_this_page; int /*<<< orphan*/  b_page; } const buffer_head ;
typedef  int __u64 ;
struct TYPE_2__ {int i_blkbits; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 struct buffer_head const* page_buffers (int /*<<< orphan*/ ) ; 
 int page_index (int /*<<< orphan*/ ) ; 

__u64 nilfs_bmap_data_get_key(const struct nilfs_bmap *bmap,
			      const struct buffer_head *bh)
{
	struct buffer_head *pbh;
	__u64 key;

	key = page_index(bh->b_page) << (PAGE_SHIFT -
					 bmap->b_inode->i_blkbits);
	for (pbh = page_buffers(bh->b_page); pbh != bh; pbh = pbh->b_this_page)
		key++;

	return key;
}