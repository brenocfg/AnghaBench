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
struct TYPE_2__ {scalar_t__ stride; scalar_t__ perm; } ;
typedef  TYPE_1__ npy_stride_sort_item ;
typedef  scalar_t__ npy_intp ;

/* Variables and functions */

__attribute__((used)) static int _npy_stride_sort_item_comparator(const void *a, const void *b)
{
    npy_intp astride = ((const npy_stride_sort_item *)a)->stride,
            bstride = ((const npy_stride_sort_item *)b)->stride;

    /* Sort the absolute value of the strides */
    if (astride < 0) {
        astride = -astride;
    }
    if (bstride < 0) {
        bstride = -bstride;
    }

    if (astride == bstride) {
        /*
         * Make the qsort stable by next comparing the perm order.
         * (Note that two perm entries will never be equal)
         */
        npy_intp aperm = ((const npy_stride_sort_item *)a)->perm,
                bperm = ((const npy_stride_sort_item *)b)->perm;
        return (aperm < bperm) ? -1 : 1;
    }
    if (astride > bstride) {
        return -1;
    }
    return 1;
}