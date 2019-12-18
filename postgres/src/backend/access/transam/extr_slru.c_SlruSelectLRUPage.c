#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ (* PagePrecedes ) (int,int) ;TYPE_1__* shared; } ;
struct TYPE_6__ {int num_slots; int* page_number; scalar_t__* page_status; int* page_lru_count; int latest_page_number; int /*<<< orphan*/ * page_dirty; int /*<<< orphan*/  cur_lru_count; } ;
typedef  TYPE_1__* SlruShared ;
typedef  TYPE_2__* SlruCtl ;

/* Variables and functions */
 scalar_t__ SLRU_PAGE_EMPTY ; 
 scalar_t__ SLRU_PAGE_VALID ; 
 int /*<<< orphan*/  SimpleLruWaitIO (TYPE_2__*,int) ; 
 int /*<<< orphan*/  SlruInternalWritePage (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int,int) ; 
 scalar_t__ stub2 (int,int) ; 

__attribute__((used)) static int
SlruSelectLRUPage(SlruCtl ctl, int pageno)
{
	SlruShared	shared = ctl->shared;

	/* Outer loop handles restart after I/O */
	for (;;)
	{
		int			slotno;
		int			cur_count;
		int			bestvalidslot = 0;	/* keep compiler quiet */
		int			best_valid_delta = -1;
		int			best_valid_page_number = 0; /* keep compiler quiet */
		int			bestinvalidslot = 0;	/* keep compiler quiet */
		int			best_invalid_delta = -1;
		int			best_invalid_page_number = 0;	/* keep compiler quiet */

		/* See if page already has a buffer assigned */
		for (slotno = 0; slotno < shared->num_slots; slotno++)
		{
			if (shared->page_number[slotno] == pageno &&
				shared->page_status[slotno] != SLRU_PAGE_EMPTY)
				return slotno;
		}

		/*
		 * If we find any EMPTY slot, just select that one. Else choose a
		 * victim page to replace.  We normally take the least recently used
		 * valid page, but we will never take the slot containing
		 * latest_page_number, even if it appears least recently used.  We
		 * will select a slot that is already I/O busy only if there is no
		 * other choice: a read-busy slot will not be least recently used once
		 * the read finishes, and waiting for an I/O on a write-busy slot is
		 * inferior to just picking some other slot.  Testing shows the slot
		 * we pick instead will often be clean, allowing us to begin a read at
		 * once.
		 *
		 * Normally the page_lru_count values will all be different and so
		 * there will be a well-defined LRU page.  But since we allow
		 * concurrent execution of SlruRecentlyUsed() within
		 * SimpleLruReadPage_ReadOnly(), it is possible that multiple pages
		 * acquire the same lru_count values.  In that case we break ties by
		 * choosing the furthest-back page.
		 *
		 * Notice that this next line forcibly advances cur_lru_count to a
		 * value that is certainly beyond any value that will be in the
		 * page_lru_count array after the loop finishes.  This ensures that
		 * the next execution of SlruRecentlyUsed will mark the page newly
		 * used, even if it's for a page that has the current counter value.
		 * That gets us back on the path to having good data when there are
		 * multiple pages with the same lru_count.
		 */
		cur_count = (shared->cur_lru_count)++;
		for (slotno = 0; slotno < shared->num_slots; slotno++)
		{
			int			this_delta;
			int			this_page_number;

			if (shared->page_status[slotno] == SLRU_PAGE_EMPTY)
				return slotno;
			this_delta = cur_count - shared->page_lru_count[slotno];
			if (this_delta < 0)
			{
				/*
				 * Clean up in case shared updates have caused cur_count
				 * increments to get "lost".  We back off the page counts,
				 * rather than trying to increase cur_count, to avoid any
				 * question of infinite loops or failure in the presence of
				 * wrapped-around counts.
				 */
				shared->page_lru_count[slotno] = cur_count;
				this_delta = 0;
			}
			this_page_number = shared->page_number[slotno];
			if (this_page_number == shared->latest_page_number)
				continue;
			if (shared->page_status[slotno] == SLRU_PAGE_VALID)
			{
				if (this_delta > best_valid_delta ||
					(this_delta == best_valid_delta &&
					 ctl->PagePrecedes(this_page_number,
									   best_valid_page_number)))
				{
					bestvalidslot = slotno;
					best_valid_delta = this_delta;
					best_valid_page_number = this_page_number;
				}
			}
			else
			{
				if (this_delta > best_invalid_delta ||
					(this_delta == best_invalid_delta &&
					 ctl->PagePrecedes(this_page_number,
									   best_invalid_page_number)))
				{
					bestinvalidslot = slotno;
					best_invalid_delta = this_delta;
					best_invalid_page_number = this_page_number;
				}
			}
		}

		/*
		 * If all pages (except possibly the latest one) are I/O busy, we'll
		 * have to wait for an I/O to complete and then retry.  In that
		 * unhappy case, we choose to wait for the I/O on the least recently
		 * used slot, on the assumption that it was likely initiated first of
		 * all the I/Os in progress and may therefore finish first.
		 */
		if (best_valid_delta < 0)
		{
			SimpleLruWaitIO(ctl, bestinvalidslot);
			continue;
		}

		/*
		 * If the selected page is clean, we're set.
		 */
		if (!shared->page_dirty[bestvalidslot])
			return bestvalidslot;

		/*
		 * Write the page.
		 */
		SlruInternalWritePage(ctl, bestvalidslot, NULL);

		/*
		 * Now loop back and try again.  This is the easiest way of dealing
		 * with corner cases such as the victim page being re-dirtied while we
		 * wrote it.
		 */
	}
}