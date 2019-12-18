#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * tp_mro; } ;
typedef  TYPE_1__ PyTypeObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_OBJECT ; 
 int /*<<< orphan*/ * PyArray_DescrFromType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyArray_DescrFromTypeObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PyTuple_GET_SIZE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyArray_Descr *
_descr_from_subtype(PyObject *type)
{
    PyObject *mro;
    mro = ((PyTypeObject *)type)->tp_mro;
    if (PyTuple_GET_SIZE(mro) < 2) {
        return PyArray_DescrFromType(NPY_OBJECT);
    }
    return PyArray_DescrFromTypeObject(PyTuple_GET_ITEM(mro, 1));
}