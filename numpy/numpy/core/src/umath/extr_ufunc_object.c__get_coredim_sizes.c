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
typedef  scalar_t__ npy_intp ;
struct TYPE_4__ {int nin; int nout; int* core_offsets; int* core_num_dims; int* core_dim_ixs; int /*<<< orphan*/  core_signature; } ;
typedef  TYPE_1__ PyUFuncObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 scalar_t__ PyArray_DIM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int const PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  REMAP_AXIS (int,int) ; 
 int UFUNC_CORE_DIM_MISSING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ufunc_get_name_cstr (TYPE_1__*) ; 

__attribute__((used)) static int
_get_coredim_sizes(PyUFuncObject *ufunc, PyArrayObject **op,
                   const int *op_core_num_dims, npy_uint32 *core_dim_flags,
                   npy_intp *core_dim_sizes, int **remap_axis) {
    int i;
    int nin = ufunc->nin;
    int nout = ufunc->nout;
    int nop = nin + nout;

    for (i = 0; i < nop; ++i) {
        if (op[i] != NULL) {
            int idim;
            int dim_offset = ufunc->core_offsets[i];
            int core_start_dim = PyArray_NDIM(op[i]) - op_core_num_dims[i];
            int dim_delta = 0;

            /* checked before this routine gets called */
            assert(core_start_dim >= 0);

            /*
             * Make sure every core dimension exactly matches all other core
             * dimensions with the same label. Note that flexible dimensions
             * may have been removed at this point, if so, they are marked
             * with UFUNC_CORE_DIM_MISSING.
             */
            for (idim = 0; idim < ufunc->core_num_dims[i]; ++idim) {
                int core_index = dim_offset + idim;
                int core_dim_index = ufunc->core_dim_ixs[core_index];
                npy_intp core_dim_size = core_dim_sizes[core_dim_index];
                npy_intp op_dim_size;

                /* can only happen if flexible; dimension missing altogether */
                if (core_dim_flags[core_dim_index] & UFUNC_CORE_DIM_MISSING) {
                    op_dim_size = 1;
                    dim_delta++; /* for indexing in dimensions */
                }
                else {
                    op_dim_size = PyArray_DIM(op[i],
                             REMAP_AXIS(i, core_start_dim + idim - dim_delta));
                }
                if (core_dim_sizes[core_dim_index] < 0) {
                    core_dim_sizes[core_dim_index] = op_dim_size;
                }
                else if (op_dim_size != core_dim_size) {
                    PyErr_Format(PyExc_ValueError,
                            "%s: %s operand %d has a mismatch in its "
                            "core dimension %d, with gufunc "
                            "signature %s (size %zd is different "
                            "from %zd)",
                            ufunc_get_name_cstr(ufunc), i < nin ? "Input" : "Output",
                            i < nin ? i : i - nin, idim - dim_delta,
                            ufunc->core_signature, op_dim_size,
                            core_dim_sizes[core_dim_index]);
                    return -1;
                }
            }
        }
    }

    /*
     * Make sure no core dimension is unspecified.
     */
    for (i = nin; i < nop; ++i) {
        int idim;
        int dim_offset = ufunc->core_offsets[i];

        for (idim = 0; idim < ufunc->core_num_dims[i]; ++idim) {
            int core_dim_index = ufunc->core_dim_ixs[dim_offset + idim];

            /* check all cases where the size has not yet been set */
            if (core_dim_sizes[core_dim_index] < 0) {
                /*
                 * Oops, this dimension was never specified
                 * (can only happen if output op not given)
                 */
                PyErr_Format(PyExc_ValueError,
                        "%s: Output operand %d has core dimension %d "
                        "unspecified, with gufunc signature %s",
                        ufunc_get_name_cstr(ufunc), i - nin, idim,
                        ufunc->core_signature);
                return -1;
            }
        }
    }

    return 0;
}