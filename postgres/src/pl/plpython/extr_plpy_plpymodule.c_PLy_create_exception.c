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
 int /*<<< orphan*/  PLy_elog (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyErr_NewException (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyModule_AddObject (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
PLy_create_exception(char *name, PyObject *base, PyObject *dict,
					 const char *modname, PyObject *mod)
{
	PyObject   *exc;

	exc = PyErr_NewException(name, base, dict);
	if (exc == NULL)
		PLy_elog(ERROR, NULL);

	/*
	 * PyModule_AddObject does not add a refcount to the object, for some odd
	 * reason; we must do that.
	 */
	Py_INCREF(exc);
	PyModule_AddObject(mod, modname, exc);

	/*
	 * The caller will also store a pointer to the exception object in some
	 * permanent variable, so add another ref to account for that.  This is
	 * probably excessively paranoid, but let's be sure.
	 */
	Py_INCREF(exc);
	return exc;
}