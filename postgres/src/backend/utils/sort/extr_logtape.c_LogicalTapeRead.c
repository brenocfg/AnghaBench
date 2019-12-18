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
struct TYPE_7__ {scalar_t__ pos; scalar_t__ nbytes; size_t buffer; int /*<<< orphan*/  writing; } ;
struct TYPE_6__ {int nTapes; TYPE_2__* tapes; } ;
typedef  TYPE_1__ LogicalTapeSet ;
typedef  TYPE_2__ LogicalTape ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ltsReadFillBuffer (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (void*,size_t,size_t) ; 

size_t
LogicalTapeRead(LogicalTapeSet *lts, int tapenum,
				void *ptr, size_t size)
{
	LogicalTape *lt;
	size_t		nread = 0;
	size_t		nthistime;

	Assert(tapenum >= 0 && tapenum < lts->nTapes);
	lt = &lts->tapes[tapenum];
	Assert(!lt->writing);

	while (size > 0)
	{
		if (lt->pos >= lt->nbytes)
		{
			/* Try to load more data into buffer. */
			if (!ltsReadFillBuffer(lts, lt))
				break;			/* EOF */
		}

		nthistime = lt->nbytes - lt->pos;
		if (nthistime > size)
			nthistime = size;
		Assert(nthistime > 0);

		memcpy(ptr, lt->buffer + lt->pos, nthistime);

		lt->pos += nthistime;
		ptr = (void *) ((char *) ptr + nthistime);
		size -= nthistime;
		nread += nthistime;
	}

	return nread;
}