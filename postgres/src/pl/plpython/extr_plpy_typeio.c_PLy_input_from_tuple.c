#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PLyExecutionContext ;
typedef  int /*<<< orphan*/  PLyDatumToOb ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PLyDict_FromTuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * PLy_current_execution_context () ; 
 int /*<<< orphan*/  PLy_get_scratch_context (int /*<<< orphan*/ *) ; 

PyObject *
PLy_input_from_tuple(PLyDatumToOb *arg, HeapTuple tuple, TupleDesc desc, bool include_generated)
{
	PyObject   *dict;
	PLyExecutionContext *exec_ctx = PLy_current_execution_context();
	MemoryContext scratch_context = PLy_get_scratch_context(exec_ctx);
	MemoryContext oldcontext;

	/*
	 * As in PLy_input_convert, do the work in the scratch context.
	 */
	MemoryContextReset(scratch_context);

	oldcontext = MemoryContextSwitchTo(scratch_context);

	dict = PLyDict_FromTuple(arg, tuple, desc, include_generated);

	MemoryContextSwitchTo(oldcontext);

	return dict;
}