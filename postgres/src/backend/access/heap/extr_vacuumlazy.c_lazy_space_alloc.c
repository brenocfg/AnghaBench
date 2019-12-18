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
struct TYPE_3__ {int max_dead_tuples; scalar_t__ dead_tuples; scalar_t__ num_dead_tuples; scalar_t__ useindex; } ;
typedef  TYPE_1__ LVRelStats ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  scalar_t__ ItemPointer ;
typedef  long BlockNumber ;

/* Variables and functions */
 int INT_MAX ; 
 scalar_t__ IsAutoVacuumWorkerProcess () ; 
 long LAZY_ALLOC_TUPLES ; 
 long Max (long,long) ; 
 int MaxAllocSize ; 
 long MaxHeapTuplesPerPage ; 
 long Min (long,int) ; 
 int autovacuum_work_mem ; 
 int maintenance_work_mem ; 
 scalar_t__ palloc (long) ; 

__attribute__((used)) static void
lazy_space_alloc(LVRelStats *vacrelstats, BlockNumber relblocks)
{
	long		maxtuples;
	int			vac_work_mem = IsAutoVacuumWorkerProcess() &&
	autovacuum_work_mem != -1 ?
	autovacuum_work_mem : maintenance_work_mem;

	if (vacrelstats->useindex)
	{
		maxtuples = (vac_work_mem * 1024L) / sizeof(ItemPointerData);
		maxtuples = Min(maxtuples, INT_MAX);
		maxtuples = Min(maxtuples, MaxAllocSize / sizeof(ItemPointerData));

		/* curious coding here to ensure the multiplication can't overflow */
		if ((BlockNumber) (maxtuples / LAZY_ALLOC_TUPLES) > relblocks)
			maxtuples = relblocks * LAZY_ALLOC_TUPLES;

		/* stay sane if small maintenance_work_mem */
		maxtuples = Max(maxtuples, MaxHeapTuplesPerPage);
	}
	else
	{
		maxtuples = MaxHeapTuplesPerPage;
	}

	vacrelstats->num_dead_tuples = 0;
	vacrelstats->max_dead_tuples = (int) maxtuples;
	vacrelstats->dead_tuples = (ItemPointer)
		palloc(maxtuples * sizeof(ItemPointerData));
}