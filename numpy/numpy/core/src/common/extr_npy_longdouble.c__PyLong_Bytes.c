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
 int /*<<< orphan*/ * PyUnicode_AsUTF8String (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
_PyLong_Bytes(PyObject *long_obj) {
    PyObject *bytes;
#if defined(NPY_PY3K)
    PyObject *unicode = PyObject_Str(long_obj);
    if (unicode == NULL) {
        return NULL;
    }
    bytes = PyUnicode_AsUTF8String(unicode);
    Py_DECREF(unicode);
#else
    bytes = PyObject_Str(long_obj);
#endif
    return bytes;
}