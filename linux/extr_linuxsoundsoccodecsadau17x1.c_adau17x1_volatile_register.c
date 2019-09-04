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
#define  ADAU17X1_PLL_CONTROL 128 

bool adau17x1_volatile_register(struct device *dev, unsigned int reg)
{
	/* SigmaDSP parameter and program memory */
	if (reg < 0x4000)
		return true;

	switch (reg) {
	/* The PLL register is 6 bytes long */
	case ADAU17X1_PLL_CONTROL:
	case ADAU17X1_PLL_CONTROL + 1:
	case ADAU17X1_PLL_CONTROL + 2:
	case ADAU17X1_PLL_CONTROL + 3:
	case ADAU17X1_PLL_CONTROL + 4:
	case ADAU17X1_PLL_CONTROL + 5:
		return true;
	default:
		break;
	}

	return false;
}