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
typedef  int Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int PyInt ;

/* Variables and functions */
 int /*<<< orphan*/  ENC_OPT ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int PyBytes_AsStringAndSize (int /*<<< orphan*/ *,char**,int*) ; 
 scalar_t__ PyBytes_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_FORMAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SET_VIM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/ * PyUnicode_AsEncodedString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_TYPE_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ alloc (unsigned int) ; 
 char* memchr (char*,char,int) ; 

__attribute__((used)) static char *
StringToLine(PyObject *obj)
{
    char	*str;
    char	*save;
    PyObject	*bytes = NULL;
    Py_ssize_t	len = 0;
    PyInt	i;
    char	*p;

    if (PyBytes_Check(obj))
    {
	if (PyBytes_AsStringAndSize(obj, &str, &len) == -1
		|| str == NULL)
	    return NULL;
    }
    else if (PyUnicode_Check(obj))
    {
	if (!(bytes = PyUnicode_AsEncodedString(obj, ENC_OPT, NULL)))
	    return NULL;

	if (PyBytes_AsStringAndSize(bytes, &str, &len) == -1
		|| str == NULL)
	{
	    Py_DECREF(bytes);
	    return NULL;
	}
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

    /*
     * Error checking: String must not contain newlines, as we
     * are replacing a single line, and we must replace it with
     * a single line.
     * A trailing newline is removed, so that append(f.readlines()) works.
     */
    p = memchr(str, '\n', len);
    if (p != NULL)
    {
	if (p == str + len - 1)
	    --len;
	else
	{
	    PyErr_SET_VIM(N_("string cannot contain newlines"));
	    Py_XDECREF(bytes);
	    return NULL;
	}
    }

    /* Create a copy of the string, with internal nulls replaced by
     * newline characters, as is the vim convention.
     */
    save = (char *)alloc((unsigned)(len+1));
    if (save == NULL)
    {
	PyErr_NoMemory();
	Py_XDECREF(bytes);
	return NULL;
    }

    for (i = 0; i < len; ++i)
    {
	if (str[i] == '\0')
	    save[i] = '\n';
	else
	    save[i] = str[i];
    }

    save[i] = '\0';
    Py_XDECREF(bytes);  /* Python 2 does nothing here */

    return save;
}