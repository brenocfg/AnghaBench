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
struct device {int dummy; } ;

/* Variables and functions */
#define  DA7210_A_CP_MODE 131 
#define  DA7210_A_HID_UNLOCK 130 
#define  DA7210_A_PLL1 129 
#define  DA7210_A_TEST_UNLOCK 128 

__attribute__((used)) static bool da7210_readable_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case DA7210_A_HID_UNLOCK:
	case DA7210_A_TEST_UNLOCK:
	case DA7210_A_PLL1:
	case DA7210_A_CP_MODE:
		return false;
	default:
		return true;
	}
}