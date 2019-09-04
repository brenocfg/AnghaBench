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
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  LapackError ; 
 int /*<<< orphan*/  PyArray_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ISBYTESWAPPED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_IS_C_CONTIGUOUS (int /*<<< orphan*/ *) ; 
 int PyArray_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,char*,char*,...) ; 

__attribute__((used)) static int
check_object(PyObject *ob, int t, char *obname,
                        char *tname, char *funname)
{
    if (!PyArray_Check(ob)) {
        PyErr_Format(LapackError,
                     "Expected an array for parameter %s in lapack_lite.%s",
                     obname, funname);
        return 0;
    }
    else if (!PyArray_IS_C_CONTIGUOUS((PyArrayObject *)ob)) {
        PyErr_Format(LapackError,
                     "Parameter %s is not contiguous in lapack_lite.%s",
                     obname, funname);
        return 0;
    }
    else if (!(PyArray_TYPE((PyArrayObject *)ob) == t)) {
        PyErr_Format(LapackError,
                     "Parameter %s is not of type %s in lapack_lite.%s",
                     obname, tname, funname);
        return 0;
    }
    else if (PyArray_ISBYTESWAPPED((PyArrayObject *)ob)) {
        PyErr_Format(LapackError,
                     "Parameter %s has non-native byte order in lapack_lite.%s",
                     obname, funname);
        return 0;
    }
    else {
        return 1;
    }
}