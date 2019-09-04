#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  kind; } ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 TYPE_1__* PyArray_DESCR (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int dtype_kind_to_simplified_ordering (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
should_use_min_scalar(PyArrayObject **op, int nop)
{
    int i, use_min_scalar, kind;
    int all_scalars = 1, max_scalar_kind = -1, max_array_kind = -1;

    /*
     * Determine if there are any scalars, and if so, whether
     * the maximum "kind" of the scalars surpasses the maximum
     * "kind" of the arrays
     */
    use_min_scalar = 0;
    if (nop > 1) {
        for(i = 0; i < nop; ++i) {
            kind = dtype_kind_to_simplified_ordering(
                                PyArray_DESCR(op[i])->kind);
            if (PyArray_NDIM(op[i]) == 0) {
                if (kind > max_scalar_kind) {
                    max_scalar_kind = kind;
                }
            }
            else {
                all_scalars = 0;
                if (kind > max_array_kind) {
                    max_array_kind = kind;
                }

            }
        }

        /* Indicate whether to use the min_scalar_type function */
        if (!all_scalars && max_array_kind >= max_scalar_kind) {
            use_min_scalar = 1;
        }
    }

    return use_min_scalar;
}