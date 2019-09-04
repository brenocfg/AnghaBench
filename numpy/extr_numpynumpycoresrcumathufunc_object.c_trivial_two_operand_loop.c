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
typedef  scalar_t__ npy_intp ;
typedef  int /*<<< orphan*/  (* PyUFuncGenericFunction ) (char**,scalar_t__*,scalar_t__*,void*) ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_BEGIN_THREADS_DEF ; 
 int /*<<< orphan*/  NPY_BEGIN_THREADS_THRESHOLDED (scalar_t__) ; 
 int /*<<< orphan*/  NPY_END_THREADS ; 
 int /*<<< orphan*/  NPY_UF_DBG_PRINT1 (char*,int) ; 
 int /*<<< orphan*/  PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_PREPARE_TRIVIAL_PAIR_ITERATION (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,char*,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ PyDataType_REFCHK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
trivial_two_operand_loop(PyArrayObject **op,
                    PyUFuncGenericFunction innerloop,
                    void *innerloopdata)
{
    char *data[2];
    npy_intp count[2], stride[2];
    int needs_api;
    NPY_BEGIN_THREADS_DEF;

    needs_api = PyDataType_REFCHK(PyArray_DESCR(op[0])) ||
                PyDataType_REFCHK(PyArray_DESCR(op[1]));

    PyArray_PREPARE_TRIVIAL_PAIR_ITERATION(op[0], op[1],
                                            count[0],
                                            data[0], data[1],
                                            stride[0], stride[1]);
    count[1] = count[0];
    NPY_UF_DBG_PRINT1("two operand loop count %d\n", (int)count[0]);

    if (!needs_api) {
        NPY_BEGIN_THREADS_THRESHOLDED(count[0]);
    }

    innerloop(data, count, stride, innerloopdata);

    NPY_END_THREADS;
}