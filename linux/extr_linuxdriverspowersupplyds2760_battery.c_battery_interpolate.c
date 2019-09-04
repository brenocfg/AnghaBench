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

__attribute__((used)) static int battery_interpolate(int array[], int temp)
{
	int index, dt;

	if (temp <= 0)
		return array[0];
	if (temp >= 40)
		return array[4];

	index = temp / 10;
	dt    = temp % 10;

	return array[index] + (((array[index + 1] - array[index]) * dt) / 10);
}