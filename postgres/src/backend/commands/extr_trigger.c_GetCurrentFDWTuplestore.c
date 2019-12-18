#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Tuplestorestate ;
struct TYPE_4__ {size_t query_depth; TYPE_1__* query_stack; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fdw_tuplestore; } ;
typedef  int /*<<< orphan*/  ResourceOwner ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  CurTransactionContext ; 
 int /*<<< orphan*/  CurTransactionResourceOwner ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 TYPE_2__ afterTriggers ; 
 int /*<<< orphan*/ * tuplestore_begin_heap (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_mem ; 

__attribute__((used)) static Tuplestorestate *
GetCurrentFDWTuplestore(void)
{
	Tuplestorestate *ret;

	ret = afterTriggers.query_stack[afterTriggers.query_depth].fdw_tuplestore;
	if (ret == NULL)
	{
		MemoryContext oldcxt;
		ResourceOwner saveResourceOwner;

		/*
		 * Make the tuplestore valid until end of subtransaction.  We really
		 * only need it until AfterTriggerEndQuery().
		 */
		oldcxt = MemoryContextSwitchTo(CurTransactionContext);
		saveResourceOwner = CurrentResourceOwner;
		CurrentResourceOwner = CurTransactionResourceOwner;

		ret = tuplestore_begin_heap(false, false, work_mem);

		CurrentResourceOwner = saveResourceOwner;
		MemoryContextSwitchTo(oldcxt);

		afterTriggers.query_stack[afterTriggers.query_depth].fdw_tuplestore = ret;
	}

	return ret;
}