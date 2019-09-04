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
typedef  int /*<<< orphan*/  npy_uint32 ;
typedef  int npy_intp ;
typedef  int npy_int8 ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  int /*<<< orphan*/  NpyIter_AxisData ;
typedef  int /*<<< orphan*/  NpyIter ;

/* Variables and functions */
 char** NAD_PTRS (int /*<<< orphan*/ *) ; 
 int* NAD_STRIDES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NIT_ADVANCE_AXISDATA (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * NIT_AXISDATA (int /*<<< orphan*/ *) ; 
 int NIT_AXISDATA_SIZEOF (int /*<<< orphan*/ ,int,int) ; 
 int* NIT_BASEOFFSETS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NIT_ITFLAGS (int /*<<< orphan*/ *) ; 
 int NIT_NDIM (int /*<<< orphan*/ *) ; 
 int NIT_NOP (int /*<<< orphan*/ *) ; 
 int* NIT_PERM (int /*<<< orphan*/ *) ; 
 char** NIT_RESETDATAPTR (int /*<<< orphan*/ *) ; 
 int PyArray_DIM (int /*<<< orphan*/ *,int) ; 
 int PyArray_STRIDE (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
npyiter_replace_axisdata(NpyIter *iter, int iop,
                      PyArrayObject *op,
                      int op_ndim, char *op_dataptr,
                      int *op_axes)
{
    npy_uint32 itflags = NIT_ITFLAGS(iter);
    int idim, ndim = NIT_NDIM(iter);
    int nop = NIT_NOP(iter);

    NpyIter_AxisData *axisdata0, *axisdata;
    npy_intp sizeof_axisdata;
    npy_int8 *perm;
    npy_intp baseoffset = 0;

    perm = NIT_PERM(iter);
    axisdata0 = NIT_AXISDATA(iter);
    sizeof_axisdata = NIT_AXISDATA_SIZEOF(itflags, ndim, nop);

    /*
     * Replace just the strides which were non-zero, and compute
     * the base data address.
     */
    axisdata = axisdata0;

    if (op_axes != NULL) {
        for (idim = 0; idim < ndim; ++idim, NIT_ADVANCE_AXISDATA(axisdata, 1)) {
            npy_int8 p;
            int i;
            npy_intp shape;

            /* Apply the perm to get the original axis */
            p = perm[idim];
            if (p < 0) {
                i = op_axes[ndim+p];
            }
            else {
                i = op_axes[ndim-p-1];
            }

            if (0 <= i && i < op_ndim) {
                shape = PyArray_DIM(op, i);
                if (shape != 1) {
                    npy_intp stride = PyArray_STRIDE(op, i);
                    if (p < 0) {
                        /* If the perm entry is negative, flip the axis */
                        NAD_STRIDES(axisdata)[iop] = -stride;
                        baseoffset += stride*(shape-1);
                    }
                    else {
                        NAD_STRIDES(axisdata)[iop] = stride;
                    }
                }
            }
        }
    }
    else {
        for (idim = 0; idim < ndim; ++idim, NIT_ADVANCE_AXISDATA(axisdata, 1)) {
            npy_int8 p;
            int i;
            npy_intp shape;

            /* Apply the perm to get the original axis */
            p = perm[idim];
            if (p < 0) {
                i = op_ndim+p;
            }
            else {
                i = op_ndim-p-1;
            }

            if (i >= 0) {
                shape = PyArray_DIM(op, i);
                if (shape != 1) {
                    npy_intp stride = PyArray_STRIDE(op, i);
                    if (p < 0) {
                        /* If the perm entry is negative, flip the axis */
                        NAD_STRIDES(axisdata)[iop] = -stride;
                        baseoffset += stride*(shape-1);
                    }
                    else {
                        NAD_STRIDES(axisdata)[iop] = stride;
                    }
                }
            }
        }
    }

    op_dataptr += baseoffset;

    /* Now the base data pointer is calculated, set it everywhere it's needed */
    NIT_RESETDATAPTR(iter)[iop] = op_dataptr;
    NIT_BASEOFFSETS(iter)[iop] = baseoffset;
    axisdata = axisdata0;
    /* Fill at least one axisdata, for the 0-d case */
    NAD_PTRS(axisdata)[iop] = op_dataptr;
    NIT_ADVANCE_AXISDATA(axisdata, 1);
    for (idim = 1; idim < ndim; ++idim, NIT_ADVANCE_AXISDATA(axisdata, 1)) {
        NAD_PTRS(axisdata)[iop] = op_dataptr;
    }
}