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
typedef  scalar_t__ npy_uintp ;
typedef  scalar_t__ npy_intp ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 scalar_t__ PyArray_DATA (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_DIM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PyArray_DIMS (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ITEMSIZE (int /*<<< orphan*/ *) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_STRIDES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  offset_bounds_from_strides (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static void
get_array_memory_extents(PyArrayObject *arr,
                         npy_uintp *out_start, npy_uintp *out_end,
                         npy_uintp *num_bytes)
{
    npy_intp low, upper;
    int j;
    offset_bounds_from_strides(PyArray_ITEMSIZE(arr), PyArray_NDIM(arr),
                               PyArray_DIMS(arr), PyArray_STRIDES(arr),
                               &low, &upper);
    *out_start = (npy_uintp)PyArray_DATA(arr) + (npy_uintp)low;
    *out_end = (npy_uintp)PyArray_DATA(arr) + (npy_uintp)upper;

    *num_bytes = PyArray_ITEMSIZE(arr);
    for (j = 0; j < PyArray_NDIM(arr); ++j) {
        *num_bytes *= PyArray_DIM(arr, j);
    }
}