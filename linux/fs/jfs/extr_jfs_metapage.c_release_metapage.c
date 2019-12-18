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
struct metapage {scalar_t__ lsn; int /*<<< orphan*/  sb; int /*<<< orphan*/  flag; scalar_t__ nohomeok; scalar_t__ count; struct page* page; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  META_dirty ; 
 int /*<<< orphan*/  META_sync ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drop_metapage (struct page*,struct metapage*) ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jfs_info (char*,struct metapage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  remove_from_logsync (struct metapage*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_metapage (struct metapage*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 scalar_t__ write_one_page (struct page*) ; 

void release_metapage(struct metapage * mp)
{
	struct page *page = mp->page;
	jfs_info("release_metapage: mp = 0x%p, flag = 0x%lx", mp, mp->flag);

	BUG_ON(!page);

	lock_page(page);
	unlock_metapage(mp);

	assert(mp->count);
	if (--mp->count || mp->nohomeok) {
		unlock_page(page);
		put_page(page);
		return;
	}

	if (test_bit(META_dirty, &mp->flag)) {
		set_page_dirty(page);
		if (test_bit(META_sync, &mp->flag)) {
			clear_bit(META_sync, &mp->flag);
			if (write_one_page(page))
				jfs_error(mp->sb, "write_one_page() failed\n");
			lock_page(page); /* write_one_page unlocks the page */
		}
	} else if (mp->lsn)	/* discard_metapage doesn't remove it */
		remove_from_logsync(mp);

	/* Try to keep metapages from using up too much memory */
	drop_metapage(page, mp);

	unlock_page(page);
	put_page(page);
}