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
struct TYPE_5__ {int /*<<< orphan*/  outer_tuples; int /*<<< orphan*/  inner_tuples; } ;
struct TYPE_4__ {int nbatch; TYPE_2__* batches; } ;
typedef  TYPE_1__* HashJoinTable ;

/* Variables and functions */
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 
 int /*<<< orphan*/  sts_end_parallel_scan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sts_end_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ExecParallelHashCloseBatchAccessors(HashJoinTable hashtable)
{
	int			i;

	for (i = 0; i < hashtable->nbatch; ++i)
	{
		/* Make sure no files are left open. */
		sts_end_write(hashtable->batches[i].inner_tuples);
		sts_end_write(hashtable->batches[i].outer_tuples);
		sts_end_parallel_scan(hashtable->batches[i].inner_tuples);
		sts_end_parallel_scan(hashtable->batches[i].outer_tuples);
	}
	pfree(hashtable->batches);
	hashtable->batches = NULL;
}