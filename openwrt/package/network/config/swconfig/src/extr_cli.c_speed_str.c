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

__attribute__((used)) static const char *
speed_str(int speed)
{
	switch (speed) {
	case 10:
		return "10baseT";
	case 100:
		return "100baseT";
	case 1000:
		return "1000baseT";
	default:
		break;
	}

	return "unknown";
}