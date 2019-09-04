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
 int DIV_ROUND_UP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ HI3660_TEMP_BASE ; 
 int /*<<< orphan*/  HI3660_TEMP_STEP ; 

__attribute__((used)) static inline int hi3660_thermal_temp_to_step(int temp)
{
	return DIV_ROUND_UP(temp - HI3660_TEMP_BASE, HI3660_TEMP_STEP);
}