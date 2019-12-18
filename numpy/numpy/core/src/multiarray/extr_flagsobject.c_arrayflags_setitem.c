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
 int arrayflags_aligned_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int arrayflags_updateifcopy_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int arrayflags_writeable_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int arrayflags_writebackifcopy_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
arrayflags_setitem(PyArrayFlagsObject *self, PyObject *ind, PyObject *item)
{
    char *key;
    char buf[16];
    int n;
    if (PyUnicode_Check(ind)) {
        PyObject *tmp_str;
        tmp_str = PyUnicode_AsASCIIString(ind);
        key = PyBytes_AS_STRING(tmp_str);
        n = PyBytes_GET_SIZE(tmp_str);
        if (n > 16) n = 16;
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
    if (((n==9) && (strncmp(key, "WRITEABLE", n) == 0)) ||
        ((n==1) && (strncmp(key, "W", n) == 0))) {
        return arrayflags_writeable_set(self, item);
    }
    else if (((n==7) && (strncmp(key, "ALIGNED", n) == 0)) ||
             ((n==1) && (strncmp(key, "A", n) == 0))) {
        return arrayflags_aligned_set(self, item);
    }
    else if (((n==12) && (strncmp(key, "UPDATEIFCOPY", n) == 0)) ||
             ((n==1) && (strncmp(key, "U", n) == 0))) {
        return arrayflags_updateifcopy_set(self, item);
    }
    else if (((n==15) && (strncmp(key, "WRITEBACKIFCOPY", n) == 0)) ||
             ((n==1) && (strncmp(key, "X", n) == 0))) {
        return arrayflags_writebackifcopy_set(self, item);
    }

 fail:
    PyErr_SetString(PyExc_KeyError, "Unknown flag");
    return -1;
}