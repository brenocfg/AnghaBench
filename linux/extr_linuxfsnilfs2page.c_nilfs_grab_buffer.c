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
struct inode {int i_blkbits; } ;
struct buffer_head {int dummy; } ;
struct address_space {int dummy; } ;
typedef  unsigned long pgoff_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 struct buffer_head* __nilfs_get_page_block (struct page*,unsigned long,unsigned long,int,unsigned long) ; 
 struct page* grab_cache_page (struct address_space*,unsigned long) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

struct buffer_head *nilfs_grab_buffer(struct inode *inode,
				      struct address_space *mapping,
				      unsigned long blkoff,
				      unsigned long b_state)
{
	int blkbits = inode->i_blkbits;
	pgoff_t index = blkoff >> (PAGE_SHIFT - blkbits);
	struct page *page;
	struct buffer_head *bh;

	page = grab_cache_page(mapping, index);
	if (unlikely(!page))
		return NULL;

	bh = __nilfs_get_page_block(page, blkoff, index, blkbits, b_state);
	if (unlikely(!bh)) {
		unlock_page(page);
		put_page(page);
		return NULL;
	}
	return bh;
}