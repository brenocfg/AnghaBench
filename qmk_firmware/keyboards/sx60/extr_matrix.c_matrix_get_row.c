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
typedef  size_t uint8_t ;
typedef  int matrix_row_t ;

/* Variables and functions */
 int* matrix ; 
 int* matrix_mask ; 

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    /* Matrix mask lets you disable switches in the returned matrix data. For example, if you have a
       switch blocker installed and the switch is always pressed. */
#ifdef MATRIX_MASKED
    return matrix[row] & matrix_mask[row];
#else
    return matrix[row];
#endif
}