#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nbatch; TYPE_2__* parallel_state; int /*<<< orphan*/  area; TYPE_1__* batches; } ;
struct TYPE_6__ {int /*<<< orphan*/  batches; int /*<<< orphan*/  build_barrier; } ;
struct TYPE_5__ {int /*<<< orphan*/  outer_tuples; int /*<<< orphan*/  inner_tuples; } ;
typedef  TYPE_2__ ParallelHashJoinState ;
typedef  TYPE_3__* HashJoinTable ;

/* Variables and functions */
 scalar_t__ BarrierDetach (int /*<<< orphan*/ *) ; 
 scalar_t__ DsaPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidDsaPointer ; 
 int /*<<< orphan*/  dsa_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sts_end_parallel_scan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sts_end_write (int /*<<< orphan*/ ) ; 

void
ExecHashTableDetach(HashJoinTable hashtable)
{
	if (hashtable->parallel_state)
	{
		ParallelHashJoinState *pstate = hashtable->parallel_state;
		int			i;

		/* Make sure any temporary files are closed. */
		if (hashtable->batches)
		{
			for (i = 0; i < hashtable->nbatch; ++i)
			{
				sts_end_write(hashtable->batches[i].inner_tuples);
				sts_end_write(hashtable->batches[i].outer_tuples);
				sts_end_parallel_scan(hashtable->batches[i].inner_tuples);
				sts_end_parallel_scan(hashtable->batches[i].outer_tuples);
			}
		}

		/* If we're last to detach, clean up shared memory. */
		if (BarrierDetach(&pstate->build_barrier))
		{
			if (DsaPointerIsValid(pstate->batches))
			{
				dsa_free(hashtable->area, pstate->batches);
				pstate->batches = InvalidDsaPointer;
			}
		}

		hashtable->parallel_state = NULL;
	}
}