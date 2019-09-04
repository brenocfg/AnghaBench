#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_2__ swp_entry_t ;
struct swap_info_struct {int flags; TYPE_4__* bdev; } ;
struct page {int dummy; } ;
struct gendisk {TYPE_1__* fops; } ;
struct TYPE_7__ {struct gendisk* bd_disk; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* swap_slot_free_notify ) (TYPE_4__*,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PageSwapCache (struct page*) ; 
 int SWP_BLKDEV ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 struct swap_info_struct* page_swap_info (struct page*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,unsigned long) ; 
 unsigned long swp_offset (TYPE_2__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void swap_slot_free_notify(struct page *page)
{
	struct swap_info_struct *sis;
	struct gendisk *disk;

	/*
	 * There is no guarantee that the page is in swap cache - the software
	 * suspend code (at least) uses end_swap_bio_read() against a non-
	 * swapcache page.  So we must check PG_swapcache before proceeding with
	 * this optimization.
	 */
	if (unlikely(!PageSwapCache(page)))
		return;

	sis = page_swap_info(page);
	if (!(sis->flags & SWP_BLKDEV))
		return;

	/*
	 * The swap subsystem performs lazy swap slot freeing,
	 * expecting that the page will be swapped out again.
	 * So we can avoid an unnecessary write if the page
	 * isn't redirtied.
	 * This is good for real swap storage because we can
	 * reduce unnecessary I/O and enhance wear-leveling
	 * if an SSD is used as the as swap device.
	 * But if in-memory swap device (eg zram) is used,
	 * this causes a duplicated copy between uncompressed
	 * data in VM-owned memory and compressed data in
	 * zram-owned memory.  So let's free zram-owned memory
	 * and make the VM-owned decompressed page *dirty*,
	 * so the page should be swapped out somewhere again if
	 * we again wish to reclaim it.
	 */
	disk = sis->bdev->bd_disk;
	if (disk->fops->swap_slot_free_notify) {
		swp_entry_t entry;
		unsigned long offset;

		entry.val = page_private(page);
		offset = swp_offset(entry);

		SetPageDirty(page);
		disk->fops->swap_slot_free_notify(sis->bdev,
				offset);
	}
}