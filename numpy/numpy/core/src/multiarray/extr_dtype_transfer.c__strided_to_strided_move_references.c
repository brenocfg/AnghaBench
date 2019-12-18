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
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_COPY_PYOBJECT_PTR (char*,char*) ; 
 int /*<<< orphan*/  NPY_DT_DBG_REFTRACE (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_strided_to_strided_move_references(char *dst, npy_intp dst_stride,
                        char *src, npy_intp src_stride,
                        npy_intp N, npy_intp src_itemsize,
                        NpyAuxData *data)
{
    PyObject *src_ref = NULL, *dst_ref = NULL;
    while (N > 0) {
        NPY_COPY_PYOBJECT_PTR(&src_ref, src);
        NPY_COPY_PYOBJECT_PTR(&dst_ref, dst);

        /* Release the reference in dst */
        NPY_DT_DBG_REFTRACE("dec dst ref", dst_ref);
        Py_XDECREF(dst_ref);
        /* Move the reference */
        NPY_DT_DBG_REFTRACE("move src ref", src_ref);
        NPY_COPY_PYOBJECT_PTR(dst, &src_ref);
        /* Set the source reference to NULL */
        src_ref = NULL;
        NPY_COPY_PYOBJECT_PTR(src, &src_ref);

        src += src_stride;
        dst += dst_stride;
        --N;
    }
}