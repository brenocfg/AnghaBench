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
typedef  scalar_t__ npy_intp ;
typedef  int /*<<< orphan*/  NpyIter_AxisData ;
typedef  int /*<<< orphan*/  NpyIter ;

/* Variables and functions */
 scalar_t__* NAD_STRIDES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NIT_ADVANCE_AXISDATA (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * NIT_AXISDATA (int /*<<< orphan*/ *) ; 
 scalar_t__ NIT_AXISDATA_SIZEOF (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  NIT_ITFLAGS (int /*<<< orphan*/ *) ; 
 int NIT_MASKOP (int /*<<< orphan*/ *) ; 
 int NIT_NDIM (int /*<<< orphan*/ *) ; 
 int NIT_NOP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 

__attribute__((used)) static int
check_mask_for_writemasked_reduction(NpyIter *iter, int iop)
{
    npy_uint32 itflags = NIT_ITFLAGS(iter);
    int idim, ndim = NIT_NDIM(iter);
    int nop = NIT_NOP(iter);
    int maskop = NIT_MASKOP(iter);

    NpyIter_AxisData *axisdata;
    npy_intp sizeof_axisdata;

    axisdata = NIT_AXISDATA(iter);
    sizeof_axisdata = NIT_AXISDATA_SIZEOF(itflags, ndim, nop);

    for(idim = 0; idim < ndim; ++idim) {
        npy_intp maskstride, istride;

        istride = NAD_STRIDES(axisdata)[iop];
        maskstride = NAD_STRIDES(axisdata)[maskop];

        /*
         * If 'iop' is being broadcast to 'maskop', we have
         * the invalid situation described above.
         */
        if (maskstride != 0 && istride == 0) {
            PyErr_SetString(PyExc_ValueError,
                    "Iterator reduction operand is WRITEMASKED, "
                    "but also broadcasts to multiple mask values. "
                    "There can be only one mask value per WRITEMASKED "
                    "element.");
            return 0;
        }

        NIT_ADVANCE_AXISDATA(axisdata, 1);
    }

    return 1;
}