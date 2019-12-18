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
typedef  int /*<<< orphan*/  npy_bool ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_FALSE ; 
 int /*<<< orphan*/  NPY_TRUE ; 
 int PyArray_ITEMSIZE (void*) ; 

__attribute__((used)) static npy_bool
_default_nonzero(void *ip, void *arr)
{
    int elsize = PyArray_ITEMSIZE(arr);
    char *ptr = ip;
    while (elsize--) {
        if (*ptr++ != 0) {
            return NPY_TRUE;
        }
    }
    return NPY_FALSE;
}