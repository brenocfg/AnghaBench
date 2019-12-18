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
typedef  int /*<<< orphan*/  _tmp_string_t ;
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 scalar_t__ PyBytes_AsStringAndSize (int /*<<< orphan*/ *,char**,scalar_t__*) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * PyUnicode_AsUTF8String (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ _append_char (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static int
_append_field_name(_tmp_string_t *str, PyObject *name)
{
    int ret = -1;
    char *p;
    Py_ssize_t len;
    PyObject *tmp;
#if defined(NPY_PY3K)
    /* FIXME: XXX -- should it use UTF-8 here? */
    tmp = PyUnicode_AsUTF8String(name);
#else
    tmp = name;
    Py_INCREF(tmp);
#endif
    if (tmp == NULL || PyBytes_AsStringAndSize(tmp, &p, &len) < 0) {
        PyErr_Clear();
        PyErr_SetString(PyExc_ValueError, "invalid field name");
        goto fail;
    }
    if (_append_char(str, ':') < 0) {
        goto fail;
    }
    while (len > 0) {
        if (*p == ':') {
            PyErr_SetString(PyExc_ValueError,
                            "':' is not an allowed character in buffer "
                            "field names");
            goto fail;
        }
        if (_append_char(str, *p) < 0) {
            goto fail;
        }
        ++p;
        --len;
    }
    if (_append_char(str, ':') < 0) {
        goto fail;
    }
    ret = 0;
fail:
    Py_XDECREF(tmp);
    return ret;
}