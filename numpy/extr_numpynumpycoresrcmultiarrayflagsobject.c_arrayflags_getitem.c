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
typedef  int /*<<< orphan*/  PyArrayFlagsObject ;

/* Variables and functions */
 char* PyBytes_AS_STRING (int /*<<< orphan*/ *) ; 
 scalar_t__ PyBytes_Check (int /*<<< orphan*/ *) ; 
 int PyBytes_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_KeyError ; 
 int /*<<< orphan*/ * PyUnicode_AsASCIIString (int /*<<< orphan*/ *) ; 
 scalar_t__ PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arrayflags_aligned_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arrayflags_behaved_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arrayflags_carray_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arrayflags_contiguous_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arrayflags_farray_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arrayflags_fnc_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arrayflags_forc_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arrayflags_fortran_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arrayflags_owndata_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arrayflags_updateifcopy_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arrayflags_writeable_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arrayflags_writebackifcopy_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static PyObject *
arrayflags_getitem(PyArrayFlagsObject *self, PyObject *ind)
{
    char *key = NULL;
    char buf[16];
    int n;
    if (PyUnicode_Check(ind)) {
        PyObject *tmp_str;
        tmp_str = PyUnicode_AsASCIIString(ind);
        if (tmp_str == NULL) {
            return NULL;
        }
        key = PyBytes_AS_STRING(tmp_str);
        n = PyBytes_GET_SIZE(tmp_str);
        if (n > 16) {
            Py_DECREF(tmp_str);
            goto fail;
        }
        memcpy(buf, key, n);
        Py_DECREF(tmp_str);
        key = buf;
    }
    else if (PyBytes_Check(ind)) {
        key = PyBytes_AS_STRING(ind);
        n = PyBytes_GET_SIZE(ind);
    }
    else {
        goto fail;
    }
    switch(n) {
    case 1:
        switch(key[0]) {
        case 'C':
            return arrayflags_contiguous_get(self);
        case 'F':
            return arrayflags_fortran_get(self);
        case 'W':
            return arrayflags_writeable_get(self);
        case 'B':
            return arrayflags_behaved_get(self);
        case 'O':
            return arrayflags_owndata_get(self);
        case 'A':
            return arrayflags_aligned_get(self);
        case 'X':
            return arrayflags_writebackifcopy_get(self);
        case 'U':
            return arrayflags_updateifcopy_get(self);
        default:
            goto fail;
        }
        break;
    case 2:
        if (strncmp(key, "CA", n) == 0) {
            return arrayflags_carray_get(self);
        }
        if (strncmp(key, "FA", n) == 0) {
            return arrayflags_farray_get(self);
        }
        break;
    case 3:
        if (strncmp(key, "FNC", n) == 0) {
            return arrayflags_fnc_get(self);
        }
        break;
    case 4:
        if (strncmp(key, "FORC", n) == 0) {
            return arrayflags_forc_get(self);
        }
        break;
    case 6:
        if (strncmp(key, "CARRAY", n) == 0) {
            return arrayflags_carray_get(self);
        }
        if (strncmp(key, "FARRAY", n) == 0) {
            return arrayflags_farray_get(self);
        }
        break;
    case 7:
        if (strncmp(key,"FORTRAN",n) == 0) {
            return arrayflags_fortran_get(self);
        }
        if (strncmp(key,"BEHAVED",n) == 0) {
            return arrayflags_behaved_get(self);
        }
        if (strncmp(key,"OWNDATA",n) == 0) {
            return arrayflags_owndata_get(self);
        }
        if (strncmp(key,"ALIGNED",n) == 0) {
            return arrayflags_aligned_get(self);
        }
        break;
    case 9:
        if (strncmp(key,"WRITEABLE",n) == 0) {
            return arrayflags_writeable_get(self);
        }
        break;
    case 10:
        if (strncmp(key,"CONTIGUOUS",n) == 0) {
            return arrayflags_contiguous_get(self);
        }
        break;
    case 12:
        if (strncmp(key, "UPDATEIFCOPY", n) == 0) {
            return arrayflags_updateifcopy_get(self);
        }
        if (strncmp(key, "C_CONTIGUOUS", n) == 0) {
            return arrayflags_contiguous_get(self);
        }
        if (strncmp(key, "F_CONTIGUOUS", n) == 0) {
            return arrayflags_fortran_get(self);
        }
        break;
    case 15:
        if (strncmp(key, "WRITEBACKIFCOPY", n) == 0) {
            return arrayflags_writebackifcopy_get(self);
        }
        break;
    }

 fail:
    PyErr_SetString(PyExc_KeyError, "Unknown flag");
    return NULL;
}