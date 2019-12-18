#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_data; } ;
struct TYPE_5__ {scalar_t__ fn_xmin; int /*<<< orphan*/  fn_tid; } ;
typedef  TYPE_1__ PLyProcedure ;
typedef  TYPE_2__* HeapTuple ;

/* Variables and functions */
 scalar_t__ HeapTupleHeaderGetRawXmin (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemPointerEquals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
PLy_procedure_valid(PLyProcedure *proc, HeapTuple procTup)
{
	if (proc == NULL)
		return false;

	/* If the pg_proc tuple has changed, it's not valid */
	if (!(proc->fn_xmin == HeapTupleHeaderGetRawXmin(procTup->t_data) &&
		  ItemPointerEquals(&proc->fn_tid, &procTup->t_self)))
		return false;

	return true;
}