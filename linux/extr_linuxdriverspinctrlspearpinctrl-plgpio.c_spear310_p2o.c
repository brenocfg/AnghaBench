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

__attribute__((used)) static int spear310_p2o(int pin)
{
	int offset = pin;

	if (pin <= 27)
		offset += 4;
	else if (pin <= 33)
		offset = -1;
	else if (pin <= 97)
		offset -= 2;
	else if (pin <= 101)
		offset = 101 - pin;
	else
		offset = -1;

	return offset;
}