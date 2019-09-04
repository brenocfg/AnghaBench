#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  npy_uint32 ;
typedef  int /*<<< orphan*/  npy_intp ;
struct TYPE_3__ {int nargs; int* core_num_dims; int core_num_dim_ix; int /*<<< orphan*/ * core_dim_flags; int /*<<< orphan*/ * core_dim_sizes; } ;
typedef  TYPE_1__ PyUFuncObject ;

/* Variables and functions */

__attribute__((used)) static int
_initialize_variable_parts(PyUFuncObject *ufunc,
                           int op_core_num_dims[],
                           npy_intp core_dim_sizes[],
                           npy_uint32 core_dim_flags[]) {
    int i;

    for (i = 0; i < ufunc->nargs; i++) {
        op_core_num_dims[i] = ufunc->core_num_dims[i];
    }
    for (i = 0; i < ufunc->core_num_dim_ix; i++) {
        core_dim_sizes[i] = ufunc->core_dim_sizes[i];
        core_dim_flags[i] = ufunc->core_dim_flags[i];
    }
    return 0;
}