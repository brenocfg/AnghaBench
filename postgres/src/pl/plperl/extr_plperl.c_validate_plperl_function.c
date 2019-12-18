#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* proc_ptr; } ;
typedef  TYPE_1__ plperl_proc_ptr ;
struct TYPE_8__ {scalar_t__ fn_xmin; int /*<<< orphan*/  fn_tid; } ;
typedef  TYPE_2__ plperl_proc_desc ;
struct TYPE_9__ {int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_data; } ;
typedef  TYPE_3__* HeapTuple ;

/* Variables and functions */
 scalar_t__ HeapTupleHeaderGetRawXmin (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemPointerEquals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decrement_prodesc_refcount (TYPE_2__*) ; 

__attribute__((used)) static bool
validate_plperl_function(plperl_proc_ptr *proc_ptr, HeapTuple procTup)
{
	if (proc_ptr && proc_ptr->proc_ptr)
	{
		plperl_proc_desc *prodesc = proc_ptr->proc_ptr;
		bool		uptodate;

		/************************************************************
		 * If it's present, must check whether it's still up to date.
		 * This is needed because CREATE OR REPLACE FUNCTION can modify the
		 * function's pg_proc entry without changing its OID.
		 ************************************************************/
		uptodate = (prodesc->fn_xmin == HeapTupleHeaderGetRawXmin(procTup->t_data) &&
					ItemPointerEquals(&prodesc->fn_tid, &procTup->t_self));

		if (uptodate)
			return true;

		/* Otherwise, unlink the obsoleted entry from the hashtable ... */
		proc_ptr->proc_ptr = NULL;
		/* ... and release the corresponding refcount, probably deleting it */
		decrement_prodesc_refcount(prodesc);
	}

	return false;
}