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
 int HI3660_TEMP_BASE ; 
 int HI3660_TEMP_STEP ; 

__attribute__((used)) static inline int hi3660_thermal_step_to_temp(int step)
{
	return HI3660_TEMP_BASE + step * HI3660_TEMP_STEP;
}