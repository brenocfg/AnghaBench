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
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyObject_IsInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npy_cache_import (char*,char*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static inline PyObject *
NpyPath_PathlikeToFspath(PyObject *file)
{
    static PyObject *os_PathLike = NULL;
    static PyObject *os_fspath = NULL;
    npy_cache_import("numpy.compat", "os_PathLike", &os_PathLike);
    if (os_PathLike == NULL) {
        return NULL;
    }
    npy_cache_import("numpy.compat", "os_fspath", &os_fspath);
    if (os_fspath == NULL) {
        return NULL;
    }

    if (!PyObject_IsInstance(file, os_PathLike)) {
        Py_INCREF(file);
        return file;
    }
    return PyObject_CallFunctionObjArgs(os_fspath, file, NULL);
}