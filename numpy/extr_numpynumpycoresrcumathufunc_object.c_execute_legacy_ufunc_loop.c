#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ufunc_full_args ;
typedef  int /*<<< orphan*/  npy_uint32 ;
typedef  int npy_intp ;
struct TYPE_6__ {int nin; int nout; scalar_t__ (* legacy_inner_loop_selector ) (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,void**,int*) ;} ;
typedef  TYPE_1__ PyUFuncObject ;
typedef  int /*<<< orphan*/  PyUFuncGenericFunction ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  scalar_t__ NPY_ORDER ;

/* Variables and functions */
 scalar_t__ NPY_ANYORDER ; 
 int /*<<< orphan*/  NPY_ARRAY_F_CONTIGUOUS ; 
 scalar_t__ NPY_KEEPORDER ; 
 int /*<<< orphan*/  NPY_UF_DBG_PRINT (char*) ; 
 int /*<<< orphan*/  PyArray_DIMS (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ISFORTRAN (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_NDIM (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_NewFromDescr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_TRIVIALLY_ITERABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_TRIVIALLY_ITERABLE_OP_NOREAD ; 
 int /*<<< orphan*/  PyArray_TRIVIALLY_ITERABLE_OP_READ ; 
 scalar_t__ PyArray_TRIVIALLY_ITERABLE_PAIR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_TRIVIALLY_ITERABLE_TRIPLE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_Type ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 scalar_t__ _does_loop_use_arrays (void*) ; 
 scalar_t__ iterator_loop (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,scalar_t__,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ prepare_ufunc_output (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,void**,int*) ; 
 int /*<<< orphan*/  trivial_three_operand_loop (int /*<<< orphan*/ **,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  trivial_two_operand_loop (int /*<<< orphan*/ **,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
execute_legacy_ufunc_loop(PyUFuncObject *ufunc,
                    int trivial_loop_ok,
                    PyArrayObject **op,
                    PyArray_Descr **dtypes,
                    NPY_ORDER order,
                    npy_intp buffersize,
                    PyObject **arr_prep,
                    ufunc_full_args full_args,
                    npy_uint32 *op_flags)
{
    npy_intp nin = ufunc->nin, nout = ufunc->nout;
    PyUFuncGenericFunction innerloop;
    void *innerloopdata;
    int needs_api = 0;

    if (ufunc->legacy_inner_loop_selector(ufunc, dtypes,
                    &innerloop, &innerloopdata, &needs_api) < 0) {
        return -1;
    }
    /* If the loop wants the arrays, provide them. */
    if (_does_loop_use_arrays(innerloopdata)) {
        innerloopdata = (void*)op;
    }

    /* First check for the trivial cases that don't need an iterator */
    if (trivial_loop_ok) {
        if (nin == 1 && nout == 1) {
            if (op[1] == NULL &&
                        (order == NPY_ANYORDER || order == NPY_KEEPORDER) &&
                        PyArray_TRIVIALLY_ITERABLE(op[0])) {
                Py_INCREF(dtypes[1]);
                op[1] = (PyArrayObject *)PyArray_NewFromDescr(&PyArray_Type,
                             dtypes[1],
                             PyArray_NDIM(op[0]),
                             PyArray_DIMS(op[0]),
                             NULL, NULL,
                             PyArray_ISFORTRAN(op[0]) ?
                                            NPY_ARRAY_F_CONTIGUOUS : 0,
                             NULL);
                if (op[1] == NULL) {
                    return -1;
                }

                /* Call the __prepare_array__ if necessary */
                if (prepare_ufunc_output(ufunc, &op[1],
                                    arr_prep[0], full_args, 0) < 0) {
                    return -1;
                }

                NPY_UF_DBG_PRINT("trivial 1 input with allocated output\n");
                trivial_two_operand_loop(op, innerloop, innerloopdata);

                return 0;
            }
            else if (op[1] != NULL &&
                        PyArray_NDIM(op[1]) >= PyArray_NDIM(op[0]) &&
                        PyArray_TRIVIALLY_ITERABLE_PAIR(op[0], op[1],
                                                        PyArray_TRIVIALLY_ITERABLE_OP_READ,
                                                        PyArray_TRIVIALLY_ITERABLE_OP_NOREAD)) {

                /* Call the __prepare_array__ if necessary */
                if (prepare_ufunc_output(ufunc, &op[1],
                                    arr_prep[0], full_args, 0) < 0) {
                    return -1;
                }

                NPY_UF_DBG_PRINT("trivial 1 input\n");
                trivial_two_operand_loop(op, innerloop, innerloopdata);

                return 0;
            }
        }
        else if (nin == 2 && nout == 1) {
            if (op[2] == NULL &&
                        (order == NPY_ANYORDER || order == NPY_KEEPORDER) &&
                        PyArray_TRIVIALLY_ITERABLE_PAIR(op[0], op[1],
                                                        PyArray_TRIVIALLY_ITERABLE_OP_READ,
                                                        PyArray_TRIVIALLY_ITERABLE_OP_READ)) {
                PyArrayObject *tmp;
                /*
                 * Have to choose the input with more dimensions to clone, as
                 * one of them could be a scalar.
                 */
                if (PyArray_NDIM(op[0]) >= PyArray_NDIM(op[1])) {
                    tmp = op[0];
                }
                else {
                    tmp = op[1];
                }
                Py_INCREF(dtypes[2]);
                op[2] = (PyArrayObject *)PyArray_NewFromDescr(&PyArray_Type,
                                 dtypes[2],
                                 PyArray_NDIM(tmp),
                                 PyArray_DIMS(tmp),
                                 NULL, NULL,
                                 PyArray_ISFORTRAN(tmp) ?
                                                NPY_ARRAY_F_CONTIGUOUS : 0,
                                 NULL);
                if (op[2] == NULL) {
                    return -1;
                }

                /* Call the __prepare_array__ if necessary */
                if (prepare_ufunc_output(ufunc, &op[2],
                                    arr_prep[0], full_args, 0) < 0) {
                    return -1;
                }

                NPY_UF_DBG_PRINT("trivial 2 input with allocated output\n");
                trivial_three_operand_loop(op, innerloop, innerloopdata);

                return 0;
            }
            else if (op[2] != NULL &&
                    PyArray_NDIM(op[2]) >= PyArray_NDIM(op[0]) &&
                    PyArray_NDIM(op[2]) >= PyArray_NDIM(op[1]) &&
                    PyArray_TRIVIALLY_ITERABLE_TRIPLE(op[0], op[1], op[2],
                                                      PyArray_TRIVIALLY_ITERABLE_OP_READ,
                                                      PyArray_TRIVIALLY_ITERABLE_OP_READ,
                                                      PyArray_TRIVIALLY_ITERABLE_OP_NOREAD)) {

                /* Call the __prepare_array__ if necessary */
                if (prepare_ufunc_output(ufunc, &op[2],
                                    arr_prep[0], full_args, 0) < 0) {
                    return -1;
                }

                NPY_UF_DBG_PRINT("trivial 2 input\n");
                trivial_three_operand_loop(op, innerloop, innerloopdata);

                return 0;
            }
        }
    }

    /*
     * If no trivial loop matched, an iterator is required to
     * resolve broadcasting, etc
     */

    NPY_UF_DBG_PRINT("iterator loop\n");
    if (iterator_loop(ufunc, op, dtypes, order,
                    buffersize, arr_prep, full_args,
                    innerloop, innerloopdata, op_flags) < 0) {
        return -1;
    }

    return 0;
}