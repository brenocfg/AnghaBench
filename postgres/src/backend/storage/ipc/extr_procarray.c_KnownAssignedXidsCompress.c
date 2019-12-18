#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int headKnownAssignedXids; int tailKnownAssignedXids; int numKnownAssignedXids; } ;
typedef  TYPE_1__ ProcArrayStruct ;

/* Variables and functions */
 int /*<<< orphan*/ * KnownAssignedXids ; 
 int* KnownAssignedXidsValid ; 
 int PROCARRAY_MAXPROCS ; 
 TYPE_1__* procArray ; 

__attribute__((used)) static void
KnownAssignedXidsCompress(bool force)
{
	ProcArrayStruct *pArray = procArray;
	int			head,
				tail;
	int			compress_index;
	int			i;

	/* no spinlock required since we hold ProcArrayLock exclusively */
	head = pArray->headKnownAssignedXids;
	tail = pArray->tailKnownAssignedXids;

	if (!force)
	{
		/*
		 * If we can choose how much to compress, use a heuristic to avoid
		 * compressing too often or not often enough.
		 *
		 * Heuristic is if we have a large enough current spread and less than
		 * 50% of the elements are currently in use, then compress. This
		 * should ensure we compress fairly infrequently. We could compress
		 * less often though the virtual array would spread out more and
		 * snapshots would become more expensive.
		 */
		int			nelements = head - tail;

		if (nelements < 4 * PROCARRAY_MAXPROCS ||
			nelements < 2 * pArray->numKnownAssignedXids)
			return;
	}

	/*
	 * We compress the array by reading the valid values from tail to head,
	 * re-aligning data to 0th element.
	 */
	compress_index = 0;
	for (i = tail; i < head; i++)
	{
		if (KnownAssignedXidsValid[i])
		{
			KnownAssignedXids[compress_index] = KnownAssignedXids[i];
			KnownAssignedXidsValid[compress_index] = true;
			compress_index++;
		}
	}

	pArray->tailKnownAssignedXids = 0;
	pArray->headKnownAssignedXids = compress_index;
}