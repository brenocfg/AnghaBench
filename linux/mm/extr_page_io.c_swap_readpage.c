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
struct swap_info_struct {int flags; int /*<<< orphan*/  bdev; struct file* swap_file; } ;
struct page {int dummy; } ;
struct gendisk {int /*<<< orphan*/  queue; } ;
struct file {struct address_space* f_mapping; } ;
struct bio {int /*<<< orphan*/  bi_private; int /*<<< orphan*/  bi_opf; struct gendisk* bi_disk; } ;
struct address_space {TYPE_1__* a_ops; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;
struct TYPE_2__ {int (* readpage ) (struct file*,struct page*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PSWPIN ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  PageSwapCache (struct page*) ; 
 int PageUptodate (struct page*) ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQ_HIPRI ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int SWP_FS ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int bdev_read_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  bio_get (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_poll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  end_swap_bio_read ; 
 scalar_t__ frontswap_load (struct page*) ; 
 struct bio* get_swap_bio (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_task_struct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_schedule () ; 
 struct swap_info_struct* page_swap_info (struct page*) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int stub1 (struct file*,struct page*) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 
 int /*<<< orphan*/  swap_page_sector (struct page*) ; 
 int /*<<< orphan*/  swap_slot_free_notify (struct page*) ; 
 scalar_t__ trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int swap_readpage(struct page *page, bool synchronous)
{
	struct bio *bio;
	int ret = 0;
	struct swap_info_struct *sis = page_swap_info(page);
	blk_qc_t qc;
	struct gendisk *disk;

	VM_BUG_ON_PAGE(!PageSwapCache(page) && !synchronous, page);
	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(PageUptodate(page), page);
	if (frontswap_load(page) == 0) {
		SetPageUptodate(page);
		unlock_page(page);
		goto out;
	}

	if (sis->flags & SWP_FS) {
		struct file *swap_file = sis->swap_file;
		struct address_space *mapping = swap_file->f_mapping;

		ret = mapping->a_ops->readpage(swap_file, page);
		if (!ret)
			count_vm_event(PSWPIN);
		return ret;
	}

	ret = bdev_read_page(sis->bdev, swap_page_sector(page), page);
	if (!ret) {
		if (trylock_page(page)) {
			swap_slot_free_notify(page);
			unlock_page(page);
		}

		count_vm_event(PSWPIN);
		return 0;
	}

	ret = 0;
	bio = get_swap_bio(GFP_KERNEL, page, end_swap_bio_read);
	if (bio == NULL) {
		unlock_page(page);
		ret = -ENOMEM;
		goto out;
	}
	disk = bio->bi_disk;
	/*
	 * Keep this task valid during swap readpage because the oom killer may
	 * attempt to access it in the page fault retry time check.
	 */
	bio_set_op_attrs(bio, REQ_OP_READ, 0);
	if (synchronous) {
		bio->bi_opf |= REQ_HIPRI;
		get_task_struct(current);
		bio->bi_private = current;
	}
	count_vm_event(PSWPIN);
	bio_get(bio);
	qc = submit_bio(bio);
	while (synchronous) {
		set_current_state(TASK_UNINTERRUPTIBLE);
		if (!READ_ONCE(bio->bi_private))
			break;

		if (!blk_poll(disk->queue, qc, true))
			io_schedule();
	}
	__set_current_state(TASK_RUNNING);
	bio_put(bio);

out:
	return ret;
}