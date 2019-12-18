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
typedef  int /*<<< orphan*/  npy_bool ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_FALSE ; 
 int /*<<< orphan*/  NPY_TRUE ; 
 int /*<<< orphan*/  PyBaseString_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyList_CheckExact (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyList_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PyList_GET_SIZE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static npy_bool
_is_list_of_strings(PyObject *obj)
{
    int seqlen, i;
    if (!PyList_CheckExact(obj)) {
        return NPY_FALSE;
    }
    seqlen = PyList_GET_SIZE(obj);
    for (i = 0; i < seqlen; i++) {
        PyObject *item = PyList_GET_ITEM(obj, i);
        if (!PyBaseString_Check(item)) {
            return NPY_FALSE;
        }
    }

    return NPY_TRUE;
}