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
struct super_block {TYPE_1__* s_bdev; } ;
struct page {struct address_space* mapping; } ;
struct inode {struct address_space* i_mapping; } ;
struct bio {int dummy; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  erofs_blk_t ;
struct TYPE_2__ {struct inode* bd_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EIO ; 
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int REQ_META ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int REQ_PRIO ; 
 int /*<<< orphan*/  __GFP_FS ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  __submit_bio (struct bio*,int /*<<< orphan*/ ,int) ; 
 int bio_add_page (struct bio*,struct page*,int,int /*<<< orphan*/ ) ; 
 struct page* find_or_create_page (struct address_space*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int mapping_gfp_constraint (struct address_space*,int /*<<< orphan*/ ) ; 
 struct bio* prepare_bio (struct super_block*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  read_endio ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

struct page *erofs_get_meta_page(struct super_block *sb,
	erofs_blk_t blkaddr, bool prio)
{
	struct inode *bd_inode = sb->s_bdev->bd_inode;
	struct address_space *mapping = bd_inode->i_mapping;
	struct page *page;

repeat:
	page = find_or_create_page(mapping, blkaddr,
	/*
	 * Prefer looping in the allocator rather than here,
	 * at least that code knows what it's doing.
	 */
		mapping_gfp_constraint(mapping, ~__GFP_FS) | __GFP_NOFAIL);

	BUG_ON(!page || !PageLocked(page));

	if (!PageUptodate(page)) {
		struct bio *bio;
		int err;

		bio = prepare_bio(sb, blkaddr, 1, read_endio);
		err = bio_add_page(bio, page, PAGE_SIZE, 0);
		BUG_ON(err != PAGE_SIZE);

		__submit_bio(bio, REQ_OP_READ,
			REQ_META | (prio ? REQ_PRIO : 0));

		lock_page(page);

		/* the page has been truncated by others? */
		if (unlikely(page->mapping != mapping)) {
			unlock_page(page);
			put_page(page);
			goto repeat;
		}

		/* more likely a read error */
		if (unlikely(!PageUptodate(page))) {
			unlock_page(page);
			put_page(page);

			page = ERR_PTR(-EIO);
		}
	}
	return page;
}