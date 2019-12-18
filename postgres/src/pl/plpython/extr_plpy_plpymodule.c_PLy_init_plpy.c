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
 int /*<<< orphan*/  PLy_add_exceptions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PLy_cursor_init_type () ; 
 int /*<<< orphan*/  PLy_elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PLy_methods ; 
 int /*<<< orphan*/  PLy_module ; 
 int /*<<< orphan*/  PLy_plan_init_type () ; 
 int /*<<< orphan*/  PLy_result_init_type () ; 
 int /*<<< orphan*/  PLy_subtransaction_init_type () ; 
 int /*<<< orphan*/  PyDict_SetItemString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/ * PyImport_AddModule (char*) ; 
 int /*<<< orphan*/  PyModule_Create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyModule_GetDict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_InitModule (char*,int /*<<< orphan*/ ) ; 

void
PLy_init_plpy(void)
{
	PyObject   *main_mod,
			   *main_dict,
			   *plpy_mod;

#if PY_MAJOR_VERSION < 3
	PyObject   *plpy;
#endif

	/*
	 * initialize plpy module
	 */
	PLy_plan_init_type();
	PLy_result_init_type();
	PLy_subtransaction_init_type();
	PLy_cursor_init_type();

#if PY_MAJOR_VERSION >= 3
	PyModule_Create(&PLy_module);
	/* for Python 3 we initialized the exceptions in PyInit_plpy */
#else
	plpy = Py_InitModule("plpy", PLy_methods);
	PLy_add_exceptions(plpy);
#endif

	/* PyDict_SetItemString(plpy, "PlanType", (PyObject *) &PLy_PlanType); */

	/*
	 * initialize main module, and add plpy
	 */
	main_mod = PyImport_AddModule("__main__");
	main_dict = PyModule_GetDict(main_mod);
	plpy_mod = PyImport_AddModule("plpy");
	if (plpy_mod == NULL)
		PLy_elog(ERROR, "could not import \"plpy\" module");
	PyDict_SetItemString(main_dict, "plpy", plpy_mod);
	if (PyErr_Occurred())
		PLy_elog(ERROR, "could not import \"plpy\" module");
}