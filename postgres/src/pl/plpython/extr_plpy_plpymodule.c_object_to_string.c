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
 int /*<<< orphan*/ * PyObject_Str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyString_AsString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
object_to_string(PyObject *obj)
{
	if (obj)
	{
		PyObject   *so = PyObject_Str(obj);

		if (so != NULL)
		{
			char	   *str;

			str = pstrdup(PyString_AsString(so));
			Py_DECREF(so);

			return str;
		}
	}

	return NULL;
}