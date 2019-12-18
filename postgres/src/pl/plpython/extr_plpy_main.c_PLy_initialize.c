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

/* Variables and functions */
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  PLy_elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * PLy_execution_contexts ; 
 int /*<<< orphan*/  PLy_init_interp () ; 
 int /*<<< orphan*/  PLy_init_plpy () ; 
 int PY_MAJOR_VERSION ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyImport_AppendInittab (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyImport_ImportModule (char*) ; 
 int /*<<< orphan*/  PyInit_plpy ; 
 int /*<<< orphan*/  Py_Initialize () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  explicit_subtransactions ; 
 int /*<<< orphan*/  init_procedure_caches () ; 
 int* plpython_version_bitmask_ptr ; 

__attribute__((used)) static void
PLy_initialize(void)
{
	static bool inited = false;

	/*
	 * Check for multiple Python libraries before actively doing anything with
	 * libpython.  This must be repeated on each entry to PL/Python, in case a
	 * conflicting library got loaded since we last looked.
	 *
	 * It is attractive to weaken this error from FATAL to ERROR, but there
	 * would be corner cases, so it seems best to be conservative.
	 */
	if (*plpython_version_bitmask_ptr != (1 << PY_MAJOR_VERSION))
		ereport(FATAL,
				(errmsg("multiple Python libraries are present in session"),
				 errdetail("Only one Python major version can be used in one session.")));

	/* The rest should only be done once per session */
	if (inited)
		return;

#if PY_MAJOR_VERSION >= 3
	PyImport_AppendInittab("plpy", PyInit_plpy);
#endif
	Py_Initialize();
#if PY_MAJOR_VERSION >= 3
	PyImport_ImportModule("plpy");
#endif
	PLy_init_interp();
	PLy_init_plpy();
	if (PyErr_Occurred())
		PLy_elog(FATAL, "untrapped error in initialization");

	init_procedure_caches();

	explicit_subtransactions = NIL;

	PLy_execution_contexts = NULL;

	inited = true;
}