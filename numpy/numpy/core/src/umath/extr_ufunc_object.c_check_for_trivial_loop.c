#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t npy_intp ;
struct TYPE_3__ {size_t nin; size_t nout; } ;
typedef  TYPE_1__ PyUFuncObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 scalar_t__ PyArray_CastToType (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_DESCR (int /*<<< orphan*/ *) ; 
 size_t PyArray_DIM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_EquivTypes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_ISALIGNED (int /*<<< orphan*/ *) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
check_for_trivial_loop(PyUFuncObject *ufunc,
                        PyArrayObject **op,
                        PyArray_Descr **dtype,
                        npy_intp buffersize)
{
    npy_intp i, nin = ufunc->nin, nop = nin + ufunc->nout;

    for (i = 0; i < nop; ++i) {
        /*
         * If the dtype doesn't match, or the array isn't aligned,
         * indicate that the trivial loop can't be done.
         */
        if (op[i] != NULL &&
                (!PyArray_ISALIGNED(op[i]) ||
                !PyArray_EquivTypes(dtype[i], PyArray_DESCR(op[i]))
                                        )) {
            /*
             * If op[j] is a scalar or small one dimensional
             * array input, make a copy to keep the opportunity
             * for a trivial loop.
             */
            if (i < nin && (PyArray_NDIM(op[i]) == 0 ||
                    (PyArray_NDIM(op[i]) == 1 &&
                     PyArray_DIM(op[i],0) <= buffersize))) {
                PyArrayObject *tmp;
                Py_INCREF(dtype[i]);
                tmp = (PyArrayObject *)
                            PyArray_CastToType(op[i], dtype[i], 0);
                if (tmp == NULL) {
                    return -1;
                }
                Py_DECREF(op[i]);
                op[i] = tmp;
            }
            else {
                return 0;
            }
        }
    }

    return 1;
}