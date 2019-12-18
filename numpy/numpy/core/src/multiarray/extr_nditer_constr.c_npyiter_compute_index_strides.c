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
typedef  int npy_uint32 ;
typedef  int npy_intp ;
typedef  int /*<<< orphan*/  NpyIter_AxisData ;
typedef  int /*<<< orphan*/  NpyIter ;

/* Variables and functions */
 scalar_t__* NAD_PTRS (int /*<<< orphan*/ *) ; 
 int NAD_SHAPE (int /*<<< orphan*/ *) ; 
 int* NAD_STRIDES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NIT_ADVANCE_AXISDATA (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * NIT_AXISDATA (int /*<<< orphan*/ *) ; 
 int NIT_AXISDATA_SIZEOF (int,int,int) ; 
 int /*<<< orphan*/ * NIT_INDEX_AXISDATA (int /*<<< orphan*/ *,int) ; 
 int NIT_ITERSIZE (int /*<<< orphan*/ *) ; 
 int NIT_ITFLAGS (int /*<<< orphan*/ *) ; 
 int NIT_NDIM (int /*<<< orphan*/ *) ; 
 int NIT_NOP (int /*<<< orphan*/ *) ; 
 int NPY_ITER_C_INDEX ; 
 int NPY_ITER_F_INDEX ; 
 int NPY_ITFLAG_HASINDEX ; 

__attribute__((used)) static void
npyiter_compute_index_strides(NpyIter *iter, npy_uint32 flags)
{
    npy_uint32 itflags = NIT_ITFLAGS(iter);
    int idim, ndim = NIT_NDIM(iter);
    int nop = NIT_NOP(iter);

    npy_intp indexstride;
    NpyIter_AxisData *axisdata;
    npy_intp sizeof_axisdata;

    /*
     * If there is only one element being iterated, we just have
     * to touch the first AXISDATA because nothing will ever be
     * incremented. This also initializes the data for the 0-d case.
     */
    if (NIT_ITERSIZE(iter) == 1) {
        if (itflags & NPY_ITFLAG_HASINDEX) {
            axisdata = NIT_AXISDATA(iter);
            NAD_PTRS(axisdata)[nop] = 0;
        }
        return;
    }

    if (flags & NPY_ITER_C_INDEX) {
        sizeof_axisdata = NIT_AXISDATA_SIZEOF(itflags, ndim, nop);
        axisdata = NIT_AXISDATA(iter);
        indexstride = 1;
        for(idim = 0; idim < ndim; ++idim, NIT_ADVANCE_AXISDATA(axisdata, 1)) {
            npy_intp shape = NAD_SHAPE(axisdata);

            if (shape == 1) {
                NAD_STRIDES(axisdata)[nop] = 0;
            }
            else {
                NAD_STRIDES(axisdata)[nop] = indexstride;
            }
            NAD_PTRS(axisdata)[nop] = 0;
            indexstride *= shape;
        }
    }
    else if (flags & NPY_ITER_F_INDEX) {
        sizeof_axisdata = NIT_AXISDATA_SIZEOF(itflags, ndim, nop);
        axisdata = NIT_INDEX_AXISDATA(NIT_AXISDATA(iter), ndim-1);
        indexstride = 1;
        for(idim = 0; idim < ndim; ++idim, NIT_ADVANCE_AXISDATA(axisdata, -1)) {
            npy_intp shape = NAD_SHAPE(axisdata);

            if (shape == 1) {
                NAD_STRIDES(axisdata)[nop] = 0;
            }
            else {
                NAD_STRIDES(axisdata)[nop] = indexstride;
            }
            NAD_PTRS(axisdata)[nop] = 0;
            indexstride *= shape;
        }
    }
}