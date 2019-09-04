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
typedef  int /*<<< orphan*/  npy_uint32 ;
typedef  int Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_ITER_ALIGNED ; 
 int /*<<< orphan*/  NPY_ITER_ALLOCATE ; 
 int /*<<< orphan*/  NPY_ITER_ARRAYMASK ; 
 int /*<<< orphan*/  NPY_ITER_CONTIG ; 
 int /*<<< orphan*/  NPY_ITER_COPY ; 
 int /*<<< orphan*/  NPY_ITER_NBO ; 
 int /*<<< orphan*/  NPY_ITER_NO_BROADCAST ; 
 int /*<<< orphan*/  NPY_ITER_NO_SUBTYPE ; 
 int /*<<< orphan*/  NPY_ITER_OVERLAP_ASSUME_ELEMENTWISE ; 
 int /*<<< orphan*/  NPY_ITER_READONLY ; 
 int /*<<< orphan*/  NPY_ITER_READWRITE ; 
 int /*<<< orphan*/  NPY_ITER_UPDATEIFCOPY ; 
 int /*<<< orphan*/  NPY_ITER_VIRTUAL ; 
 int /*<<< orphan*/  NPY_ITER_WRITEMASKED ; 
 int /*<<< orphan*/  NPY_ITER_WRITEONLY ; 
 scalar_t__ PyBytes_AsStringAndSize (int /*<<< orphan*/ *,char**,int*) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  PyList_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PySequence_GetItem (int /*<<< orphan*/ *,int) ; 
 int PySequence_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyTuple_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyUnicode_AsASCIIString (int /*<<< orphan*/ *) ; 
 scalar_t__ PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int
NpyIter_OpFlagsConverter(PyObject *op_flags_in,
                         npy_uint32 *op_flags)
{
    int iflags, nflags;
    npy_uint32 flag;

    if (!PyTuple_Check(op_flags_in) && !PyList_Check(op_flags_in)) {
        PyErr_SetString(PyExc_ValueError,
                "op_flags must be a tuple or array of per-op flag-tuples");
        return 0;
    }

    nflags = PySequence_Size(op_flags_in);

    *op_flags = 0;
    for (iflags = 0; iflags < nflags; ++iflags) {
        PyObject *f;
        char *str = NULL;
        Py_ssize_t length = 0;

        f = PySequence_GetItem(op_flags_in, iflags);
        if (f == NULL) {
            return 0;
        }

        if (PyUnicode_Check(f)) {
            /* accept unicode input */
            PyObject *f_str;
            f_str = PyUnicode_AsASCIIString(f);
            if (f_str == NULL) {
                Py_DECREF(f);
                return 0;
            }
            Py_DECREF(f);
            f = f_str;
        }

        if (PyBytes_AsStringAndSize(f, &str, &length) < 0) {
            PyErr_Clear();
            Py_DECREF(f);
            PyErr_SetString(PyExc_ValueError,
                   "op_flags must be a tuple or array of per-op flag-tuples");
            return 0;
        }

        /* Use switch statements to quickly isolate the right flag */
        flag = 0;
        switch (str[0]) {
            case 'a':
                if (length > 2) switch(str[2]) {
                    case 'i':
                        if (strcmp(str, "aligned") == 0) {
                            flag = NPY_ITER_ALIGNED;
                        }
                        break;
                    case 'l':
                        if (strcmp(str, "allocate") == 0) {
                            flag = NPY_ITER_ALLOCATE;
                        }
                        break;
                    case 'r':
                        if (strcmp(str, "arraymask") == 0) {
                            flag = NPY_ITER_ARRAYMASK;
                        }
                        break;
                }
                break;
            case 'c':
                if (strcmp(str, "copy") == 0) {
                    flag = NPY_ITER_COPY;
                }
                if (strcmp(str, "contig") == 0) {
                    flag = NPY_ITER_CONTIG;
                }
                break;
            case 'n':
                switch (str[1]) {
                    case 'b':
                        if (strcmp(str, "nbo") == 0) {
                            flag = NPY_ITER_NBO;
                        }
                        break;
                    case 'o':
                        if (strcmp(str, "no_subtype") == 0) {
                            flag = NPY_ITER_NO_SUBTYPE;
                        }
                        else if (strcmp(str, "no_broadcast") == 0) {
                            flag = NPY_ITER_NO_BROADCAST;
                        }
                        break;
                }
                break;
            case 'o':
                if (strcmp(str, "overlap_assume_elementwise") == 0) {
                    flag = NPY_ITER_OVERLAP_ASSUME_ELEMENTWISE;
                }
                break;
            case 'r':
                if (length > 4) switch (str[4]) {
                    case 'o':
                        if (strcmp(str, "readonly") == 0) {
                            flag = NPY_ITER_READONLY;
                        }
                        break;
                    case 'w':
                        if (strcmp(str, "readwrite") == 0) {
                            flag = NPY_ITER_READWRITE;
                        }
                        break;
                }
                break;
            case 'u':
                switch (str[1]) {
                    case 'p':
                        if (strcmp(str, "updateifcopy") == 0) {
                            flag = NPY_ITER_UPDATEIFCOPY;
                        }
                        break;
                }
                break;
            case 'v':
                if (strcmp(str, "virtual") == 0) {
                    flag = NPY_ITER_VIRTUAL;
                }
                break;
            case 'w':
                if (length > 5) switch (str[5]) {
                    case 'o':
                        if (strcmp(str, "writeonly") == 0) {
                            flag = NPY_ITER_WRITEONLY;
                        }
                        break;
                    case 'm':
                        if (strcmp(str, "writemasked") == 0) {
                            flag = NPY_ITER_WRITEMASKED;
                        }
                        break;
                }
                break;
        }
        if (flag == 0) {
            PyErr_Format(PyExc_ValueError,
                    "Unexpected per-op iterator flag \"%s\"", str);
            Py_DECREF(f);
            return 0;
        }
        else {
            *op_flags |= flag;
        }
        Py_DECREF(f);
    }

    return 1;
}