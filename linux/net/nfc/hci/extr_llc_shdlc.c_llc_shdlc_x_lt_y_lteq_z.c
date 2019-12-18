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

__attribute__((used)) static bool llc_shdlc_x_lt_y_lteq_z(int x, int y, int z)
{
	if (x < z)
		return ((x < y) && (y <= z)) ? true : false;
	else
		return ((y > x) || (y <= z)) ? true : false;
}