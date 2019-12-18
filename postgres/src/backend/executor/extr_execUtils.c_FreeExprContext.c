#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  es_exprcontexts; } ;
struct TYPE_7__ {TYPE_2__* ecxt_estate; int /*<<< orphan*/  ecxt_per_tuple_memory; } ;
typedef  TYPE_1__ ExprContext ;
typedef  TYPE_2__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShutdownExprContext (TYPE_1__*,int) ; 
 int /*<<< orphan*/  list_delete_ptr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
FreeExprContext(ExprContext *econtext, bool isCommit)
{
	EState	   *estate;

	/* Call any registered callbacks */
	ShutdownExprContext(econtext, isCommit);
	/* And clean up the memory used */
	MemoryContextDelete(econtext->ecxt_per_tuple_memory);
	/* Unlink self from owning EState, if any */
	estate = econtext->ecxt_estate;
	if (estate)
		estate->es_exprcontexts = list_delete_ptr(estate->es_exprcontexts,
												  econtext);
	/* And delete the ExprContext node */
	pfree(econtext);
}