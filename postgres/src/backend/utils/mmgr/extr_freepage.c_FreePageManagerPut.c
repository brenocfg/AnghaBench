#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ contiguous_pages; scalar_t__ free_pages; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_1__ FreePageManager ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FreePageBtreeCleanup (TYPE_1__*) ; 
 scalar_t__ FreePageManagerLargestContiguous (TYPE_1__*) ; 
 scalar_t__ FreePageManagerPutInternal (TYPE_1__*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  FreePageManagerUpdateLargest (TYPE_1__*) ; 
 scalar_t__ sum_free_pages (TYPE_1__*) ; 

void
FreePageManagerPut(FreePageManager *fpm, Size first_page, Size npages)
{
	Size		contiguous_pages;

	Assert(npages > 0);

	/* Record the new pages. */
	contiguous_pages =
		FreePageManagerPutInternal(fpm, first_page, npages, false);

	/*
	 * If the new range we inserted into the page manager was contiguous with
	 * an existing range, it may have opened up cleanup opportunities.
	 */
	if (contiguous_pages > npages)
	{
		Size		cleanup_contiguous_pages;

		cleanup_contiguous_pages = FreePageBtreeCleanup(fpm);
		if (cleanup_contiguous_pages > contiguous_pages)
			contiguous_pages = cleanup_contiguous_pages;
	}

	/* See if we now have a new largest chunk. */
	if (fpm->contiguous_pages < contiguous_pages)
		fpm->contiguous_pages = contiguous_pages;

	/*
	 * The earlier call to FreePageManagerPutInternal may have set
	 * contiguous_pages_dirty if it needed to allocate internal pages, so
	 * recompute contiguous_pages if necessary.
	 */
	FreePageManagerUpdateLargest(fpm);

#ifdef FPM_EXTRA_ASSERTS
	fpm->free_pages += npages;
	Assert(fpm->free_pages == sum_free_pages(fpm));
	Assert(fpm->contiguous_pages == FreePageManagerLargestContiguous(fpm));
#endif
}