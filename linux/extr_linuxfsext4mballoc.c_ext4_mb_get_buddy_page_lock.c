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
struct super_block {int s_blocksize; } ;
struct page {scalar_t__ mapping; } ;
struct inode {scalar_t__ i_mapping; } ;
struct ext4_buddy {struct page* bd_buddy_page; scalar_t__ bd_bitmap; struct page* bd_bitmap_page; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int ext4_group_t ;
struct TYPE_2__ {struct inode* s_buddy_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 int PAGE_SIZE ; 
 struct page* find_or_create_page (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 

__attribute__((used)) static int ext4_mb_get_buddy_page_lock(struct super_block *sb,
		ext4_group_t group, struct ext4_buddy *e4b, gfp_t gfp)
{
	struct inode *inode = EXT4_SB(sb)->s_buddy_cache;
	int block, pnum, poff;
	int blocks_per_page;
	struct page *page;

	e4b->bd_buddy_page = NULL;
	e4b->bd_bitmap_page = NULL;

	blocks_per_page = PAGE_SIZE / sb->s_blocksize;
	/*
	 * the buddy cache inode stores the block bitmap
	 * and buddy information in consecutive blocks.
	 * So for each group we need two blocks.
	 */
	block = group * 2;
	pnum = block / blocks_per_page;
	poff = block % blocks_per_page;
	page = find_or_create_page(inode->i_mapping, pnum, gfp);
	if (!page)
		return -ENOMEM;
	BUG_ON(page->mapping != inode->i_mapping);
	e4b->bd_bitmap_page = page;
	e4b->bd_bitmap = page_address(page) + (poff * sb->s_blocksize);

	if (blocks_per_page >= 2) {
		/* buddy and bitmap are on the same page */
		return 0;
	}

	block++;
	pnum = block / blocks_per_page;
	page = find_or_create_page(inode->i_mapping, pnum, gfp);
	if (!page)
		return -ENOMEM;
	BUG_ON(page->mapping != inode->i_mapping);
	e4b->bd_buddy_page = page;
	return 0;
}