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
struct task_struct {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_2__ {scalar_t__ bi_sector; } ;
struct bio {struct task_struct* bi_private; TYPE_1__ bi_iter; scalar_t__ bi_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  WRITE_ONCE (struct task_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_dev (struct bio*) ; 
 struct page* bio_first_page_all (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  blk_wake_io_task (struct task_struct*) ; 
 int /*<<< orphan*/  pr_alert (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  swap_slot_free_notify (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void end_swap_bio_read(struct bio *bio)
{
	struct page *page = bio_first_page_all(bio);
	struct task_struct *waiter = bio->bi_private;

	if (bio->bi_status) {
		SetPageError(page);
		ClearPageUptodate(page);
		pr_alert("Read-error on swap-device (%u:%u:%llu)\n",
			 MAJOR(bio_dev(bio)), MINOR(bio_dev(bio)),
			 (unsigned long long)bio->bi_iter.bi_sector);
		goto out;
	}

	SetPageUptodate(page);
	swap_slot_free_notify(page);
out:
	unlock_page(page);
	WRITE_ONCE(bio->bi_private, NULL);
	bio_put(bio);
	if (waiter) {
		blk_wake_io_task(waiter);
		put_task_struct(waiter);
	}
}