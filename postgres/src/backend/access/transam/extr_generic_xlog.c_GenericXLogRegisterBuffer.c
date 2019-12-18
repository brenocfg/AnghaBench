#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* pages; } ;
struct TYPE_4__ {scalar_t__ buffer; int flags; int /*<<< orphan*/  image; } ;
typedef  TYPE_1__ PageData ;
typedef  int /*<<< orphan*/ * Page ;
typedef  TYPE_2__ GenericXLogState ;
typedef  scalar_t__ Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  BLCKSZ ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 scalar_t__ BufferIsInvalid (scalar_t__) ; 
 int /*<<< orphan*/  ERROR ; 
 int MAX_GENERIC_XLOG_PAGES ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Page
GenericXLogRegisterBuffer(GenericXLogState *state, Buffer buffer, int flags)
{
	int			block_id;

	/* Search array for existing entry or first unused slot */
	for (block_id = 0; block_id < MAX_GENERIC_XLOG_PAGES; block_id++)
	{
		PageData   *page = &state->pages[block_id];

		if (BufferIsInvalid(page->buffer))
		{
			/* Empty slot, so use it (there cannot be a match later) */
			page->buffer = buffer;
			page->flags = flags;
			memcpy(page->image, BufferGetPage(buffer), BLCKSZ);
			return (Page) page->image;
		}
		else if (page->buffer == buffer)
		{
			/*
			 * Buffer is already registered.  Just return the image, which is
			 * already prepared.
			 */
			return (Page) page->image;
		}
	}

	elog(ERROR, "maximum number %d of generic xlog buffers is exceeded",
		 MAX_GENERIC_XLOG_PAGES);
	/* keep compiler quiet */
	return NULL;
}