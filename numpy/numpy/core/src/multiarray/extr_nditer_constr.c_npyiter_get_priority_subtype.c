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
typedef  int npyiter_opitflags ;
typedef  int /*<<< orphan*/  PyTypeObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int const NPY_OP_ITFLAG_READ ; 
 double PyArray_GetPriority (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/ * Py_TYPE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
npyiter_get_priority_subtype(int nop, PyArrayObject **op,
                            const npyiter_opitflags *op_itflags,
                            double *subtype_priority,
                            PyTypeObject **subtype)
{
    int iop;

    for (iop = 0; iop < nop; ++iop) {
        if (op[iop] != NULL && op_itflags[iop] & NPY_OP_ITFLAG_READ) {
            double priority = PyArray_GetPriority((PyObject *)op[iop], 0.0);
            if (priority > *subtype_priority) {
                *subtype_priority = priority;
                *subtype = Py_TYPE(op[iop]);
            }
        }
    }
}