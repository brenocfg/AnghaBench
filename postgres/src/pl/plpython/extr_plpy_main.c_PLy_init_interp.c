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
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PLy_elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * PLy_interp_globals ; 
 int /*<<< orphan*/ * PyDict_New () ; 
 int /*<<< orphan*/  PyDict_SetItemString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/ * PyImport_AddModule (char*) ; 
 int /*<<< orphan*/ * PyModule_GetDict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
PLy_init_interp(void)
{
	static PyObject *PLy_interp_safe_globals = NULL;
	PyObject   *mainmod;

	mainmod = PyImport_AddModule("__main__");
	if (mainmod == NULL || PyErr_Occurred())
		PLy_elog(ERROR, "could not import \"__main__\" module");
	Py_INCREF(mainmod);
	PLy_interp_globals = PyModule_GetDict(mainmod);
	PLy_interp_safe_globals = PyDict_New();
	if (PLy_interp_safe_globals == NULL)
		PLy_elog(ERROR, NULL);
	PyDict_SetItemString(PLy_interp_globals, "GD", PLy_interp_safe_globals);
	Py_DECREF(mainmod);
	if (PLy_interp_globals == NULL || PyErr_Occurred())
		PLy_elog(ERROR, "could not initialize globals");
}