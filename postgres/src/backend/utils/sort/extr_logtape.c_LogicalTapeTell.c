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
struct TYPE_5__ {long offsetBlockNumber; scalar_t__ buffer_size; long curBlockNumber; int pos; } ;
struct TYPE_4__ {int nTapes; TYPE_2__* tapes; } ;
typedef  TYPE_1__ LogicalTapeSet ;
typedef  TYPE_2__ LogicalTape ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLCKSZ ; 

void
LogicalTapeTell(LogicalTapeSet *lts, int tapenum,
				long *blocknum, int *offset)
{
	LogicalTape *lt;

	Assert(tapenum >= 0 && tapenum < lts->nTapes);
	lt = &lts->tapes[tapenum];
	Assert(lt->offsetBlockNumber == 0L);

	/* With a larger buffer, 'pos' wouldn't be the same as offset within page */
	Assert(lt->buffer_size == BLCKSZ);

	*blocknum = lt->curBlockNumber;
	*offset = lt->pos;
}