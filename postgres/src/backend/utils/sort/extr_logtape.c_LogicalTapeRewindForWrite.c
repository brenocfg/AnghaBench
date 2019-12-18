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
struct TYPE_5__ {int writing; int dirty; long firstBlockNumber; long curBlockNumber; scalar_t__ buffer_size; int /*<<< orphan*/ * buffer; scalar_t__ nbytes; scalar_t__ pos; int /*<<< orphan*/  frozen; } ;
struct TYPE_4__ {int nTapes; TYPE_2__* tapes; } ;
typedef  TYPE_1__ LogicalTapeSet ;
typedef  TYPE_2__ LogicalTape ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

void
LogicalTapeRewindForWrite(LogicalTapeSet *lts, int tapenum)
{
	LogicalTape *lt;

	Assert(tapenum >= 0 && tapenum < lts->nTapes);
	lt = &lts->tapes[tapenum];

	Assert(!lt->writing && !lt->frozen);
	lt->writing = true;
	lt->dirty = false;
	lt->firstBlockNumber = -1L;
	lt->curBlockNumber = -1L;
	lt->pos = 0;
	lt->nbytes = 0;
	if (lt->buffer)
		pfree(lt->buffer);
	lt->buffer = NULL;
	lt->buffer_size = 0;
}