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
typedef  scalar_t__ uint ;

/* Variables and functions */

__attribute__((used)) static float map_uint_to_float(uint x, uint in_min, uint in_max, float out_min, float out_max)
{
	return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + (float)out_min;
}