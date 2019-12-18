#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* shared; } ;
struct TYPE_7__ {scalar_t__* page_status; int* page_dirty; int* page_number; int latest_page_number; int /*<<< orphan*/ * page_buffer; } ;
typedef  TYPE_1__* SlruShared ;
typedef  TYPE_2__* SlruCtl ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BLCKSZ ; 
 int /*<<< orphan*/  MemSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SLRU_PAGE_EMPTY ; 
 scalar_t__ SLRU_PAGE_VALID ; 
 int /*<<< orphan*/  SimpleLruZeroLSNs (TYPE_2__*,int) ; 
 int /*<<< orphan*/  SlruRecentlyUsed (TYPE_1__*,int) ; 
 int SlruSelectLRUPage (TYPE_2__*,int) ; 

int
SimpleLruZeroPage(SlruCtl ctl, int pageno)
{
	SlruShared	shared = ctl->shared;
	int			slotno;

	/* Find a suitable buffer slot for the page */
	slotno = SlruSelectLRUPage(ctl, pageno);
	Assert(shared->page_status[slotno] == SLRU_PAGE_EMPTY ||
		   (shared->page_status[slotno] == SLRU_PAGE_VALID &&
			!shared->page_dirty[slotno]) ||
		   shared->page_number[slotno] == pageno);

	/* Mark the slot as containing this page */
	shared->page_number[slotno] = pageno;
	shared->page_status[slotno] = SLRU_PAGE_VALID;
	shared->page_dirty[slotno] = true;
	SlruRecentlyUsed(shared, slotno);

	/* Set the buffer to zeroes */
	MemSet(shared->page_buffer[slotno], 0, BLCKSZ);

	/* Set the LSNs for this new page to zero */
	SimpleLruZeroLSNs(ctl, slotno);

	/* Assume this page is now the latest active page */
	shared->latest_page_number = pageno;

	return slotno;
}