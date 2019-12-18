#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nr_pending; TYPE_2__* pending_writebacks; } ;
typedef  TYPE_1__ WritebackContext ;
struct TYPE_8__ {scalar_t__ forkNum; scalar_t__ blockNum; int /*<<< orphan*/  rnode; } ;
struct TYPE_7__ {TYPE_3__ tag; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  SMgrRelation ;
typedef  TYPE_2__ PendingWriteback ;
typedef  TYPE_3__ BufferTag ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidBackendId ; 
 int /*<<< orphan*/  RelFileNodeEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffertag_comparator ; 
 int /*<<< orphan*/  qsort (TYPE_2__**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smgropen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smgrwriteback (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 

void
IssuePendingWritebacks(WritebackContext *context)
{
	int			i;

	if (context->nr_pending == 0)
		return;

	/*
	 * Executing the writes in-order can make them a lot faster, and allows to
	 * merge writeback requests to consecutive blocks into larger writebacks.
	 */
	qsort(&context->pending_writebacks, context->nr_pending,
		  sizeof(PendingWriteback), buffertag_comparator);

	/*
	 * Coalesce neighbouring writes, but nothing else. For that we iterate
	 * through the, now sorted, array of pending flushes, and look forward to
	 * find all neighbouring (or identical) writes.
	 */
	for (i = 0; i < context->nr_pending; i++)
	{
		PendingWriteback *cur;
		PendingWriteback *next;
		SMgrRelation reln;
		int			ahead;
		BufferTag	tag;
		Size		nblocks = 1;

		cur = &context->pending_writebacks[i];
		tag = cur->tag;

		/*
		 * Peek ahead, into following writeback requests, to see if they can
		 * be combined with the current one.
		 */
		for (ahead = 0; i + ahead + 1 < context->nr_pending; ahead++)
		{
			next = &context->pending_writebacks[i + ahead + 1];

			/* different file, stop */
			if (!RelFileNodeEquals(cur->tag.rnode, next->tag.rnode) ||
				cur->tag.forkNum != next->tag.forkNum)
				break;

			/* ok, block queued twice, skip */
			if (cur->tag.blockNum == next->tag.blockNum)
				continue;

			/* only merge consecutive writes */
			if (cur->tag.blockNum + 1 != next->tag.blockNum)
				break;

			nblocks++;
			cur = next;
		}

		i += ahead;

		/* and finally tell the kernel to write the data to storage */
		reln = smgropen(tag.rnode, InvalidBackendId);
		smgrwriteback(reln, tag.forkNum, tag.blockNum, nblocks);
	}

	context->nr_pending = 0;
}