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
struct TYPE_4__ {int nin; int nout; int* core_num_dims; int /*<<< orphan*/  core_signature; } ;
typedef  TYPE_1__ PyUFuncObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  ufunc_get_name_cstr (TYPE_1__*) ; 

__attribute__((used)) static int
_check_keepdims_support(PyUFuncObject *ufunc) {
    int i;
    int nin = ufunc->nin, nout = ufunc->nout;
    int input_core_dims = ufunc->core_num_dims[0];
    for (i = 1; i < nin + nout; i++) {
        if (ufunc->core_num_dims[i] != (i < nin ? input_core_dims : 0)) {
            PyErr_Format(PyExc_TypeError,
                "%s does not support keepdims: its signature %s requires "
                "%s %d to have %d core dimensions, but keepdims can only "
                "be used when all inputs have the same number of core "
                "dimensions and all outputs have no core dimensions.",
                ufunc_get_name_cstr(ufunc),
                ufunc->core_signature,
                i < nin ? "input" : "output",
                i < nin ? i : i - nin,
                ufunc->core_num_dims[i]);
            return -1;
        }
    }
    return 0;
}