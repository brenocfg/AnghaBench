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
struct TYPE_3__ {int /*<<< orphan*/  globals; int /*<<< orphan*/ * code; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyCodeObject ;
typedef  TYPE_1__ PLyProcedure ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_FINALLY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  PLy_abort_open_subtransactions (int volatile) ; 
 int /*<<< orphan*/  PLy_elog (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyDict_SetItemString (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyEval_EvalCode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  explicit_subtransactions ; 
 int volatile list_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
PLy_procedure_call(PLyProcedure *proc, const char *kargs, PyObject *vargs)
{
	PyObject   *rv = NULL;
	int volatile save_subxact_level = list_length(explicit_subtransactions);

	PyDict_SetItemString(proc->globals, kargs, vargs);

	PG_TRY();
	{
#if PY_VERSION_HEX >= 0x03020000
		rv = PyEval_EvalCode(proc->code,
							 proc->globals, proc->globals);
#else
		rv = PyEval_EvalCode((PyCodeObject *) proc->code,
							 proc->globals, proc->globals);
#endif

		/*
		 * Since plpy will only let you close subtransactions that you
		 * started, you cannot *unnest* subtransactions, only *nest* them
		 * without closing.
		 */
		Assert(list_length(explicit_subtransactions) >= save_subxact_level);
	}
	PG_FINALLY();
	{
		PLy_abort_open_subtransactions(save_subxact_level);
	}
	PG_END_TRY();

	/* If the Python code returned an error, propagate it */
	if (rv == NULL)
		PLy_elog(ERROR, NULL);

	return rv;
}