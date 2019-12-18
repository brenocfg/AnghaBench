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
typedef  int /*<<< orphan*/  npy_off_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * NpyPath_PathlikeToFspath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ **,char**,char**) ; 
 scalar_t__ PyArray_ToFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ PyBytes_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  Py_SETREF (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ npy_PyFile_CloseFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * npy_PyFile_Dup2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ npy_PyFile_DupClose2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npy_PyFile_OpenFile (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static PyObject *
array_tofile(PyArrayObject *self, PyObject *args, PyObject *kwds)
{
    int own;
    PyObject *file;
    FILE *fd;
    char *sep = "";
    char *format = "";
    npy_off_t orig_pos = 0;
    static char *kwlist[] = {"file", "sep", "format", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O|ss:tofile", kwlist,
                                     &file,
                                     &sep,
                                     &format)) {
        return NULL;
    }

    file = NpyPath_PathlikeToFspath(file);
    if (file == NULL) {
        return NULL;
    }
    if (PyBytes_Check(file) || PyUnicode_Check(file)) {
        Py_SETREF(file, npy_PyFile_OpenFile(file, "wb"));
        if (file == NULL) {
            return NULL;
        }
        own = 1;
    }
    else {
        own = 0;
    }

    fd = npy_PyFile_Dup2(file, "wb", &orig_pos);
    if (fd == NULL) {
        goto fail;
    }
    if (PyArray_ToFile(self, fd, sep, format) < 0) {
        goto fail;
    }
    if (npy_PyFile_DupClose2(file, fd, orig_pos) < 0) {
        goto fail;
    }
    if (own && npy_PyFile_CloseFile(file) < 0) {
        goto fail;
    }
    Py_DECREF(file);
    Py_RETURN_NONE;

fail:
    Py_DECREF(file);
    return NULL;
}