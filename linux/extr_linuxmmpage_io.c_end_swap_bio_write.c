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
struct page {int dummy; } ;
struct TYPE_2__ {scalar_t__ bi_sector; } ;
struct bio {TYPE_1__ bi_iter; scalar_t__ bi_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageReclaim (struct page*) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  bio_dev (struct bio*) ; 
 struct page* bio_first_page_all (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 int /*<<< orphan*/  pr_alert (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

void end_swap_bio_write(struct bio *bio)
{
	struct page *page = bio_first_page_all(bio);

	if (bio->bi_status) {
		SetPageError(page);
		/*
		 * We failed to write the page out to swap-space.
		 * Re-dirty the page in order to avoid it being reclaimed.
		 * Also print a dire warning that things will go BAD (tm)
		 * very quickly.
		 *
		 * Also clear PG_reclaim to avoid rotate_reclaimable_page()
		 */
		set_page_dirty(page);
		pr_alert("Write-error on swap-device (%u:%u:%llu)\n",
			 MAJOR(bio_dev(bio)), MINOR(bio_dev(bio)),
			 (unsigned long long)bio->bi_iter.bi_sector);
		ClearPageReclaim(page);
	}
	end_page_writeback(page);
	bio_put(bio);
}