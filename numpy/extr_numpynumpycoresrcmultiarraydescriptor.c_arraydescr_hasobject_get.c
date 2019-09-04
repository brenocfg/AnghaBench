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
typedef  int /*<<< orphan*/  PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_ITEM_HASOBJECT ; 
 scalar_t__ PyDataType_FLAGCHK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_RETURN_FALSE ; 
 int /*<<< orphan*/  Py_RETURN_TRUE ; 

__attribute__((used)) static PyObject *
arraydescr_hasobject_get(PyArray_Descr *self)
{
    if (PyDataType_FLAGCHK(self, NPY_ITEM_HASOBJECT)) {
        Py_RETURN_TRUE;
    }
    else {
        Py_RETURN_FALSE;
    }
}