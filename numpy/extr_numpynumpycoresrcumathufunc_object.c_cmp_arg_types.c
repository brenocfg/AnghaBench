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

/* Variables and functions */
 scalar_t__ PyArray_CanCastSafely (int,int) ; 
 scalar_t__ PyArray_EquivTypenums (int,int) ; 

__attribute__((used)) static int
cmp_arg_types(int *arg1, int *arg2, int n)
{
    for (; n > 0; n--, arg1++, arg2++) {
        if (PyArray_EquivTypenums(*arg1, *arg2)) {
            continue;
        }
        if (PyArray_CanCastSafely(*arg1, *arg2)) {
            return -1;
        }
        return 1;
    }
    return 0;
}