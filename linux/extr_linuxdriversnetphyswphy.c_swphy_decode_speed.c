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
 int EINVAL ; 
 int SWMII_SPEED_10 ; 
 int SWMII_SPEED_100 ; 
 int SWMII_SPEED_1000 ; 

__attribute__((used)) static int swphy_decode_speed(int speed)
{
	switch (speed) {
	case 1000:
		return SWMII_SPEED_1000;
	case 100:
		return SWMII_SPEED_100;
	case 10:
		return SWMII_SPEED_10;
	default:
		return -EINVAL;
	}
}