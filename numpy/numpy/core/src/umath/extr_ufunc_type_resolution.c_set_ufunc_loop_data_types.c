#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type_num; } ;
struct TYPE_5__ {int nin; int nout; } ;
typedef  TYPE_1__ PyUFuncObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 TYPE_3__* PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_DescrFromType (int) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XINCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ensure_dtype_nbo (TYPE_3__*) ; 

__attribute__((used)) static int
set_ufunc_loop_data_types(PyUFuncObject *self, PyArrayObject **op,
                    PyArray_Descr **out_dtypes,
                    int *type_nums, PyArray_Descr **dtypes)
{
    int i, nin = self->nin, nop = nin + self->nout;

    /*
     * Fill the dtypes array.
     * For outputs,
     * also search the inputs for a matching type_num to copy
     * instead of creating a new one, similarly to preserve metadata.
     **/
    for (i = 0; i < nop; ++i) {
        if (dtypes != NULL) {
            out_dtypes[i] = dtypes[i];
            Py_XINCREF(out_dtypes[i]);
        /*
         * Copy the dtype from 'op' if the type_num matches,
         * to preserve metadata.
         */
        }
        else if (op[i] != NULL &&
                 PyArray_DESCR(op[i])->type_num == type_nums[i]) {
            out_dtypes[i] = ensure_dtype_nbo(PyArray_DESCR(op[i]));
        }
        /*
         * For outputs, copy the dtype from op[0] if the type_num
         * matches, similarly to preserve metadata.
         */
        else if (i >= nin && op[0] != NULL &&
                            PyArray_DESCR(op[0])->type_num == type_nums[i]) {
            out_dtypes[i] = ensure_dtype_nbo(PyArray_DESCR(op[0]));
        }
        /* Otherwise create a plain descr from the type number */
        else {
            out_dtypes[i] = PyArray_DescrFromType(type_nums[i]);
        }

        if (out_dtypes[i] == NULL) {
            goto fail;
        }
    }

    return 0;

fail:
    while (--i >= 0) {
        Py_DECREF(out_dtypes[i]);
        out_dtypes[i] = NULL;
    }
    return -1;
}