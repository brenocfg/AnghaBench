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
typedef  int /*<<< orphan*/  PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  PyBytes_AsString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyDataType_HASFIELDS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_KeyError ; 
 int /*<<< orphan*/ * PyUnicode_AsUnicodeEscapeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arraydescr_str (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
_check_has_fields(PyArray_Descr *self)
{
    if (!PyDataType_HASFIELDS(self)) {
        PyObject *astr = arraydescr_str(self);
        if (astr == NULL) {
            return -1;
        }
#if defined(NPY_PY3K)
        {
            PyObject *bstr = PyUnicode_AsUnicodeEscapeString(astr);
            Py_DECREF(astr);
            astr = bstr;
        }
#endif
        PyErr_Format(PyExc_KeyError,
                "There are no fields in dtype %s.", PyBytes_AsString(astr));
        Py_DECREF(astr);
        return -1;
    }
    else {
        return 0;
    }
}