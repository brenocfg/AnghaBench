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
struct TYPE_3__ {int nin; int nout; scalar_t__* core_num_dims; } ;
typedef  TYPE_1__ PyUFuncObject ;

/* Variables and functions */

__attribute__((used)) static int
_has_output_coredims(PyUFuncObject *ufunc) {
    int i;
    for (i = ufunc->nin; i < ufunc->nin + ufunc->nout; ++i) {
        if (ufunc->core_num_dims[i] > 0) {
            return 1;
        }
    }
    return 0;
}