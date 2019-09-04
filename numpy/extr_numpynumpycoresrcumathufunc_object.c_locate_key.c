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
typedef  int npy_intp ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int PyObject_RichCompareBool (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_EQ ; 

__attribute__((used)) static npy_intp
locate_key(PyObject **kwnames, PyObject *key)
{
    PyObject **kwname = kwnames;
    while (*kwname != NULL && *kwname != key) {
        kwname++;
    }
    /* Slow fallback, just in case */
    if (*kwname == NULL) {
        int cmp = 0;
        kwname = kwnames;
        while (*kwname != NULL &&
               (cmp = PyObject_RichCompareBool(key, *kwname,
                                               Py_EQ)) == 0) {
            kwname++;
        }
        if (cmp < 0) {
            return -1;
        }
    }
    return kwname - kwnames;
}