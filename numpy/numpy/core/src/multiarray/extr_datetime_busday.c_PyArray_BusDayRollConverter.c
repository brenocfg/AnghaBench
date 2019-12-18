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
typedef  int /*<<< orphan*/  NPY_BUSDAY_ROLL ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_BUSDAY_BACKWARD ; 
 int /*<<< orphan*/  NPY_BUSDAY_FOLLOWING ; 
 int /*<<< orphan*/  NPY_BUSDAY_FORWARD ; 
 int /*<<< orphan*/  NPY_BUSDAY_MODIFIEDFOLLOWING ; 
 int /*<<< orphan*/  NPY_BUSDAY_MODIFIEDPRECEDING ; 
 int /*<<< orphan*/  NPY_BUSDAY_NAT ; 
 int /*<<< orphan*/  NPY_BUSDAY_PRECEDING ; 
 int /*<<< orphan*/  NPY_BUSDAY_RAISE ; 
 scalar_t__ PyBytes_AsStringAndSize (int /*<<< orphan*/ *,char**,int*) ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * PyUnicode_AsASCIIString (int /*<<< orphan*/ *) ; 
 scalar_t__ PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int
PyArray_BusDayRollConverter(PyObject *roll_in, NPY_BUSDAY_ROLL *roll)
{
    PyObject *obj = roll_in;
    char *str;
    Py_ssize_t len;

    /* Make obj into an ASCII string */
    Py_INCREF(obj);
    if (PyUnicode_Check(obj)) {
        /* accept unicode input */
        PyObject *obj_str;
        obj_str = PyUnicode_AsASCIIString(obj);
        if (obj_str == NULL) {
            Py_DECREF(obj);
            return 0;
        }
        Py_DECREF(obj);
        obj = obj_str;
    }

    if (PyBytes_AsStringAndSize(obj, &str, &len) < 0) {
        Py_DECREF(obj);
        return 0;
    }

    /* Use switch statements to quickly isolate the right enum value */
    switch (str[0]) {
        case 'b':
            if (strcmp(str, "backward") == 0) {
                *roll = NPY_BUSDAY_BACKWARD;
                goto finish;
            }
            break;
        case 'f':
            if (len > 2) switch (str[2]) {
                case 'r':
                    if (strcmp(str, "forward") == 0) {
                        *roll = NPY_BUSDAY_FORWARD;
                        goto finish;
                    }
                    break;
                case 'l':
                    if (strcmp(str, "following") == 0) {
                        *roll = NPY_BUSDAY_FOLLOWING;
                        goto finish;
                    }
                    break;
            }
            break;
        case 'm':
            if (len > 8) switch (str[8]) {
                case 'f':
                    if (strcmp(str, "modifiedfollowing") == 0) {
                        *roll = NPY_BUSDAY_MODIFIEDFOLLOWING;
                        goto finish;
                    }
                    break;
                case 'p':
                    if (strcmp(str, "modifiedpreceding") == 0) {
                        *roll = NPY_BUSDAY_MODIFIEDPRECEDING;
                        goto finish;
                    }
                    break;
            }
            break;
        case 'n':
            if (strcmp(str, "nat") == 0) {
                *roll = NPY_BUSDAY_NAT;
                goto finish;
            }
            break;
        case 'p':
            if (strcmp(str, "preceding") == 0) {
                *roll = NPY_BUSDAY_PRECEDING;
                goto finish;
            }
            break;
        case 'r':
            if (strcmp(str, "raise") == 0) {
                *roll = NPY_BUSDAY_RAISE;
                goto finish;
            }
            break;
    }

    PyErr_Format(PyExc_ValueError,
            "Invalid business day roll parameter \"%s\"",
            str);
    Py_DECREF(obj);
    return 0;

finish:
    Py_DECREF(obj);
    return 1;
}