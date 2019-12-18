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
 int** __dlm_compat_matrix ; 

int dlm_modes_compat(int mode1, int mode2)
{
	return __dlm_compat_matrix[mode1 + 1][mode2 + 1];
}