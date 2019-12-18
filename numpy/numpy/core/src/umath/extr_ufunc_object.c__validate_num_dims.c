#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int npy_uint32 ;
struct TYPE_4__ {int nin; int nargs; int* core_offsets; int* core_num_dims; int* core_dim_ixs; int /*<<< orphan*/  core_signature; } ;
typedef  TYPE_1__ PyUFuncObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int UFUNC_CORE_DIM_CAN_IGNORE ; 
 int UFUNC_CORE_DIM_MISSING ; 
 int /*<<< orphan*/  ufunc_get_name_cstr (TYPE_1__*) ; 

__attribute__((used)) static int
_validate_num_dims(PyUFuncObject *ufunc, PyArrayObject **op,
                   npy_uint32 *core_dim_flags,
                   int *op_core_num_dims) {
    int i, j;
    int nin = ufunc->nin;
    int nop = ufunc->nargs;

    for (i = 0; i < nop; i++) {
        if (op[i] != NULL) {
            int op_ndim = PyArray_NDIM(op[i]);

            if (op_ndim < op_core_num_dims[i]) {
                int core_offset = ufunc->core_offsets[i];
                /* We've too few, but some dimensions might be flexible */
                for (j = core_offset;
                     j < core_offset + ufunc->core_num_dims[i]; j++) {
                    int core_dim_index = ufunc->core_dim_ixs[j];
                    if ((core_dim_flags[core_dim_index] &
                         UFUNC_CORE_DIM_CAN_IGNORE)) {
                        int i1, j1, k;
                        /*
                         * Found a dimension that can be ignored. Flag that
                         * it is missing, and unflag that it can be ignored,
                         * since we are doing so already.
                         */
                        core_dim_flags[core_dim_index] |= UFUNC_CORE_DIM_MISSING;
                        core_dim_flags[core_dim_index] ^= UFUNC_CORE_DIM_CAN_IGNORE;
                        /*
                         * Reduce the number of core dimensions for all
                         * operands that use this one (including ours),
                         * and check whether we're now OK.
                         */
                        for (i1 = 0, k=0; i1 < nop; i1++) {
                            for (j1 = 0; j1 < ufunc->core_num_dims[i1]; j1++) {
                                if (ufunc->core_dim_ixs[k++] == core_dim_index) {
                                    op_core_num_dims[i1]--;
                                }
                            }
                        }
                        if (op_ndim == op_core_num_dims[i]) {
                            break;
                        }
                    }
                }
                if (op_ndim < op_core_num_dims[i]) {
                    PyErr_Format(PyExc_ValueError,
                         "%s: %s operand %d does not have enough "
                         "dimensions (has %d, gufunc core with "
                         "signature %s requires %d)",
                         ufunc_get_name_cstr(ufunc),
                         i < nin ? "Input" : "Output",
                         i < nin ? i : i - nin, PyArray_NDIM(op[i]),
                         ufunc->core_signature, op_core_num_dims[i]);
                    return -1;
                }
            }
        }
    }
    return 0;
}