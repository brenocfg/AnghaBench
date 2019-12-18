#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_9__ {TYPE_2__* pages; scalar_t__ isLogged; } ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  buffer; scalar_t__ image; int /*<<< orphan*/  deltaLen; int /*<<< orphan*/  delta; } ;
struct TYPE_7__ {scalar_t__ pd_upper; scalar_t__ pd_lower; } ;
typedef  TYPE_1__* PageHeader ;
typedef  TYPE_2__ PageData ;
typedef  scalar_t__ Page ;
typedef  TYPE_3__ GenericXLogState ;

/* Variables and functions */
 scalar_t__ BLCKSZ ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsInvalid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int GENERIC_XLOG_FULL_IMAGE ; 
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 int MAX_GENERIC_XLOG_PAGES ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int REGBUF_FORCE_IMAGE ; 
 int REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_GENERIC_ID ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  computeDelta (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 

XLogRecPtr
GenericXLogFinish(GenericXLogState *state)
{
	XLogRecPtr	lsn;
	int			i;

	if (state->isLogged)
	{
		/* Logged relation: make xlog record in critical section. */
		XLogBeginInsert();

		START_CRIT_SECTION();

		for (i = 0; i < MAX_GENERIC_XLOG_PAGES; i++)
		{
			PageData   *pageData = &state->pages[i];
			Page		page;
			PageHeader	pageHeader;

			if (BufferIsInvalid(pageData->buffer))
				continue;

			page = BufferGetPage(pageData->buffer);
			pageHeader = (PageHeader) pageData->image;

			if (pageData->flags & GENERIC_XLOG_FULL_IMAGE)
			{
				/*
				 * A full-page image does not require us to supply any xlog
				 * data.  Just apply the image, being careful to zero the
				 * "hole" between pd_lower and pd_upper in order to avoid
				 * divergence between actual page state and what replay would
				 * produce.
				 */
				memcpy(page, pageData->image, pageHeader->pd_lower);
				memset(page + pageHeader->pd_lower, 0,
					   pageHeader->pd_upper - pageHeader->pd_lower);
				memcpy(page + pageHeader->pd_upper,
					   pageData->image + pageHeader->pd_upper,
					   BLCKSZ - pageHeader->pd_upper);

				XLogRegisterBuffer(i, pageData->buffer,
								   REGBUF_FORCE_IMAGE | REGBUF_STANDARD);
			}
			else
			{
				/*
				 * In normal mode, calculate delta and write it as xlog data
				 * associated with this page.
				 */
				computeDelta(pageData, page, (Page) pageData->image);

				/* Apply the image, with zeroed "hole" as above */
				memcpy(page, pageData->image, pageHeader->pd_lower);
				memset(page + pageHeader->pd_lower, 0,
					   pageHeader->pd_upper - pageHeader->pd_lower);
				memcpy(page + pageHeader->pd_upper,
					   pageData->image + pageHeader->pd_upper,
					   BLCKSZ - pageHeader->pd_upper);

				XLogRegisterBuffer(i, pageData->buffer, REGBUF_STANDARD);
				XLogRegisterBufData(i, pageData->delta, pageData->deltaLen);
			}
		}

		/* Insert xlog record */
		lsn = XLogInsert(RM_GENERIC_ID, 0);

		/* Set LSN and mark buffers dirty */
		for (i = 0; i < MAX_GENERIC_XLOG_PAGES; i++)
		{
			PageData   *pageData = &state->pages[i];

			if (BufferIsInvalid(pageData->buffer))
				continue;
			PageSetLSN(BufferGetPage(pageData->buffer), lsn);
			MarkBufferDirty(pageData->buffer);
		}
		END_CRIT_SECTION();
	}
	else
	{
		/* Unlogged relation: skip xlog-related stuff */
		START_CRIT_SECTION();
		for (i = 0; i < MAX_GENERIC_XLOG_PAGES; i++)
		{
			PageData   *pageData = &state->pages[i];

			if (BufferIsInvalid(pageData->buffer))
				continue;
			memcpy(BufferGetPage(pageData->buffer),
				   pageData->image,
				   BLCKSZ);
			/* We don't worry about zeroing the "hole" in this case */
			MarkBufferDirty(pageData->buffer);
		}
		END_CRIT_SECTION();
		/* We don't have a LSN to return, in this case */
		lsn = InvalidXLogRecPtr;
	}

	pfree(state);

	return lsn;
}