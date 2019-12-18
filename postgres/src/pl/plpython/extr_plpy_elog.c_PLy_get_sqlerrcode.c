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
 int MAKE_SQLSTATE (char,char,char,char,char) ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 char* PyString_AsString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 
 int strspn (char*,char*) ; 

__attribute__((used)) static void
PLy_get_sqlerrcode(PyObject *exc, int *sqlerrcode)
{
	PyObject   *sqlstate;
	char	   *buffer;

	sqlstate = PyObject_GetAttrString(exc, "sqlstate");
	if (sqlstate == NULL)
		return;

	buffer = PyString_AsString(sqlstate);
	if (strlen(buffer) == 5 &&
		strspn(buffer, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ") == 5)
	{
		*sqlerrcode = MAKE_SQLSTATE(buffer[0], buffer[1], buffer[2],
									buffer[3], buffer[4]);
	}

	Py_DECREF(sqlstate);
}