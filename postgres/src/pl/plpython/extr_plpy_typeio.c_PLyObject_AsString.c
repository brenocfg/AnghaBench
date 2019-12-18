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
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * PLyUnicode_Bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PLy_elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyBytes_AsString (int /*<<< orphan*/ *) ; 
 size_t PyBytes_Size (int /*<<< orphan*/ *) ; 
 scalar_t__ PyFloat_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_Repr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_Str (int /*<<< orphan*/ *) ; 
 scalar_t__ PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pg_verifymbstr (char*,size_t,int) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

char *
PLyObject_AsString(PyObject *plrv)
{
	PyObject   *plrv_bo;
	char	   *plrv_sc;
	size_t		plen;
	size_t		slen;

	if (PyUnicode_Check(plrv))
		plrv_bo = PLyUnicode_Bytes(plrv);
	else if (PyFloat_Check(plrv))
	{
		/* use repr() for floats, str() is lossy */
#if PY_MAJOR_VERSION >= 3
		PyObject   *s = PyObject_Repr(plrv);

		plrv_bo = PLyUnicode_Bytes(s);
		Py_XDECREF(s);
#else
		plrv_bo = PyObject_Repr(plrv);
#endif
	}
	else
	{
#if PY_MAJOR_VERSION >= 3
		PyObject   *s = PyObject_Str(plrv);

		plrv_bo = PLyUnicode_Bytes(s);
		Py_XDECREF(s);
#else
		plrv_bo = PyObject_Str(plrv);
#endif
	}
	if (!plrv_bo)
		PLy_elog(ERROR, "could not create string representation of Python object");

	plrv_sc = pstrdup(PyBytes_AsString(plrv_bo));
	plen = PyBytes_Size(plrv_bo);
	slen = strlen(plrv_sc);

	Py_XDECREF(plrv_bo);

	if (slen < plen)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("could not convert Python object into cstring: Python string representation appears to contain null bytes")));
	else if (slen > plen)
		elog(ERROR, "could not convert Python object into cstring: Python string longer than reported length");
	pg_verifymbstr(plrv_sc, slen, false);

	return plrv_sc;
}