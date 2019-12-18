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
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
npyiter_calculate_ndim(int nop, PyArrayObject **op_in,
                       int oa_ndim)
{
    /* If 'op_axes' is being used, force 'ndim' */
    if (oa_ndim >= 0 ) {
        return oa_ndim;
    }
    /* Otherwise it's the maximum 'ndim' from the operands */
    else {
        int ndim = 0, iop;

        for (iop = 0; iop < nop; ++iop) {
            if (op_in[iop] != NULL) {
                int ondim = PyArray_NDIM(op_in[iop]);
                if (ondim > ndim) {
                    ndim = ondim;
                }
            }

        }

        return ndim;
    }
}