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
typedef  int /*<<< orphan*/  typval_T ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int ConvertFromPyObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EMSG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMSG2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 scalar_t__ PyErr_ExceptionMatches (int /*<<< orphan*/ ) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_PrintEx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_SystemExit ; 
 int /*<<< orphan*/ * PyRun_String (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_eval_input ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* e_py_systemexit ; 
 int /*<<< orphan*/  globals ; 
 int /*<<< orphan*/  msg_silent ; 

__attribute__((used)) static void
run_eval(const char *cmd, typval_T *rettv
#ifdef PY_CAN_RECURSE
	, PyGILState_STATE *pygilstate UNUSED
#endif
	)
{
    PyObject	*run_ret;

    run_ret = PyRun_String((char *)cmd, Py_eval_input, globals, globals);
    if (run_ret == NULL)
    {
	if (PyErr_Occurred() && PyErr_ExceptionMatches(PyExc_SystemExit))
	{
	    EMSG2(_(e_py_systemexit), "python");
	    PyErr_Clear();
	}
	else
	{
	    if (PyErr_Occurred() && !msg_silent)
		PyErr_PrintEx(0);
	    EMSG(_("E858: Eval did not return a valid python object"));
	}
    }
    else
    {
	if (ConvertFromPyObject(run_ret, rettv) == -1)
	    EMSG(_("E859: Failed to convert returned python object to vim value"));
	Py_DECREF(run_ret);
    }
    PyErr_Clear();
}