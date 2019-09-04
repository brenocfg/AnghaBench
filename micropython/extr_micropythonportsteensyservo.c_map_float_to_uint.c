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
typedef  int uint ;

/* Variables and functions */

__attribute__((used)) static uint map_float_to_uint(float x, float in_min, float in_max, uint out_min, uint out_max)
{
	return (int)((x - in_min) * (float)(out_max - out_min) / (in_max - in_min) + (float)out_min);
}