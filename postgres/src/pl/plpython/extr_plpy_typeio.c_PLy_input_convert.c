#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * (* func ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PLyExecutionContext ;
typedef  TYPE_1__ PLyDatumToOb ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PLy_current_execution_context () ; 
 int /*<<< orphan*/  PLy_get_scratch_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

PyObject *
PLy_input_convert(PLyDatumToOb *arg, Datum val)
{
	PyObject   *result;
	PLyExecutionContext *exec_ctx = PLy_current_execution_context();
	MemoryContext scratch_context = PLy_get_scratch_context(exec_ctx);
	MemoryContext oldcontext;

	/*
	 * Do the work in the scratch context to avoid leaking memory from the
	 * datatype output function calls.  (The individual PLyDatumToObFunc
	 * functions can't reset the scratch context, because they recurse and an
	 * inner one might clobber data an outer one still needs.  So we do it
	 * once at the outermost recursion level.)
	 *
	 * We reset the scratch context before, not after, each conversion cycle.
	 * This way we aren't on the hook to release a Python refcount on the
	 * result object in case MemoryContextReset throws an error.
	 */
	MemoryContextReset(scratch_context);

	oldcontext = MemoryContextSwitchTo(scratch_context);

	result = arg->func(arg, val);

	MemoryContextSwitchTo(oldcontext);

	return result;
}