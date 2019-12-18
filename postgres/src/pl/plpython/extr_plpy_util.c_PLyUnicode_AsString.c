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
 int /*<<< orphan*/ * PLyUnicode_Bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyBytes_AsString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 

char *
PLyUnicode_AsString(PyObject *unicode)
{
	PyObject   *o = PLyUnicode_Bytes(unicode);
	char	   *rv = pstrdup(PyBytes_AsString(o));

	Py_XDECREF(o);
	return rv;
}