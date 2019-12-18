#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct extent_io_tree {int dummy; } ;
struct extent_buffer {struct page** pages; int /*<<< orphan*/  io_pages; scalar_t__ read_mirror; int /*<<< orphan*/  bflags; TYPE_1__* fs_info; } ;
struct bio {int dummy; } ;
struct TYPE_4__ {struct extent_io_tree io_tree; } ;
struct TYPE_3__ {int /*<<< orphan*/  btree_inode; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearPageError (struct page*) ; 
 int EIO ; 
 int /*<<< orphan*/  EXTENT_BUFFER_READ_ERR ; 
 int /*<<< orphan*/  EXTENT_BUFFER_UPTODATE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  REQ_META ; 
 int WAIT_COMPLETE ; 
 int WAIT_NONE ; 
 int __extent_read_full_page (struct extent_io_tree*,struct page*,int /*<<< orphan*/ ,struct bio**,int,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  btree_get_extent ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int num_extent_pages (struct extent_buffer*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int submit_one_bio (struct bio*,int,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_locked (struct page*) ; 

int read_extent_buffer_pages(struct extent_buffer *eb, int wait, int mirror_num)
{
	int i;
	struct page *page;
	int err;
	int ret = 0;
	int locked_pages = 0;
	int all_uptodate = 1;
	int num_pages;
	unsigned long num_reads = 0;
	struct bio *bio = NULL;
	unsigned long bio_flags = 0;
	struct extent_io_tree *tree = &BTRFS_I(eb->fs_info->btree_inode)->io_tree;

	if (test_bit(EXTENT_BUFFER_UPTODATE, &eb->bflags))
		return 0;

	num_pages = num_extent_pages(eb);
	for (i = 0; i < num_pages; i++) {
		page = eb->pages[i];
		if (wait == WAIT_NONE) {
			if (!trylock_page(page))
				goto unlock_exit;
		} else {
			lock_page(page);
		}
		locked_pages++;
	}
	/*
	 * We need to firstly lock all pages to make sure that
	 * the uptodate bit of our pages won't be affected by
	 * clear_extent_buffer_uptodate().
	 */
	for (i = 0; i < num_pages; i++) {
		page = eb->pages[i];
		if (!PageUptodate(page)) {
			num_reads++;
			all_uptodate = 0;
		}
	}

	if (all_uptodate) {
		set_bit(EXTENT_BUFFER_UPTODATE, &eb->bflags);
		goto unlock_exit;
	}

	clear_bit(EXTENT_BUFFER_READ_ERR, &eb->bflags);
	eb->read_mirror = 0;
	atomic_set(&eb->io_pages, num_reads);
	for (i = 0; i < num_pages; i++) {
		page = eb->pages[i];

		if (!PageUptodate(page)) {
			if (ret) {
				atomic_dec(&eb->io_pages);
				unlock_page(page);
				continue;
			}

			ClearPageError(page);
			err = __extent_read_full_page(tree, page,
						      btree_get_extent, &bio,
						      mirror_num, &bio_flags,
						      REQ_META);
			if (err) {
				ret = err;
				/*
				 * We use &bio in above __extent_read_full_page,
				 * so we ensure that if it returns error, the
				 * current page fails to add itself to bio and
				 * it's been unlocked.
				 *
				 * We must dec io_pages by ourselves.
				 */
				atomic_dec(&eb->io_pages);
			}
		} else {
			unlock_page(page);
		}
	}

	if (bio) {
		err = submit_one_bio(bio, mirror_num, bio_flags);
		if (err)
			return err;
	}

	if (ret || wait != WAIT_COMPLETE)
		return ret;

	for (i = 0; i < num_pages; i++) {
		page = eb->pages[i];
		wait_on_page_locked(page);
		if (!PageUptodate(page))
			ret = -EIO;
	}

	return ret;

unlock_exit:
	while (locked_pages > 0) {
		locked_pages--;
		page = eb->pages[locked_pages];
		unlock_page(page);
	}
	return ret;
}