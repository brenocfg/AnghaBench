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
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  ENC_OPT ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int PyBytes_AsStringAndSize (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *) ; 
 scalar_t__ PyBytes_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_FORMAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/ * PyUnicode_AsEncodedString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_TYPE_NAME (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char_u *
StringToChars(PyObject *obj, PyObject **todecref)
{
    char_u	*str;

    if (PyBytes_Check(obj))
    {

	if (PyBytes_AsStringAndSize(obj, (char **) &str, NULL) == -1
		|| str == NULL)
	    return NULL;

	*todecref = NULL;
    }
    else if (PyUnicode_Check(obj))
    {
	PyObject	*bytes;

	if (!(bytes = PyUnicode_AsEncodedString(obj, ENC_OPT, NULL)))
	    return NULL;

	if(PyBytes_AsStringAndSize(bytes, (char **) &str, NULL) == -1
		|| str == NULL)
	{
	    Py_DECREF(bytes);
	    return NULL;
	}

	*todecref = bytes;
    }
    else
    {
#if PY_MAJOR_VERSION < 3
	PyErr_FORMAT(PyExc_TypeError,
		N_("expected str() or unicode() instance, but got %s"),
		Py_TYPE_NAME(obj));
#else
	PyErr_FORMAT(PyExc_TypeError,
		N_("expected bytes() or str() instance, but got %s"),
		Py_TYPE_NAME(obj));
#endif
	return NULL;
    }

    return (char_u *) str;
}