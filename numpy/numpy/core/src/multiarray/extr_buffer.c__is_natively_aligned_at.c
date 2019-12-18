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
struct TYPE_3__ {int alignment; int elsize; } ;
typedef  int Py_ssize_t ;
typedef  TYPE_1__ PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 scalar_t__ PyArray_DATA (int /*<<< orphan*/ *) ; 
 int PyArray_DIM (int /*<<< orphan*/ *,int) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int PyArray_STRIDE (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
_is_natively_aligned_at(PyArray_Descr *descr,
                        PyArrayObject *arr, Py_ssize_t offset)
{
    int k;

    if ((Py_ssize_t)(PyArray_DATA(arr)) % descr->alignment != 0) {
        return 0;
    }

    if (offset % descr->alignment != 0) {
        return 0;
    }

    if (descr->elsize % descr->alignment) {
        return 0;
    }

    for (k = 0; k < PyArray_NDIM(arr); ++k) {
        if (PyArray_DIM(arr, k) > 1) {
            if (PyArray_STRIDE(arr, k) % descr->alignment != 0) {
                return 0;
            }
        }
    }

    return 1;
}