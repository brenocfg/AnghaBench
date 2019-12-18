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
#define  SGTL5000_CHIP_ADCDAC_CTRL 130 
#define  SGTL5000_CHIP_ANA_STATUS 129 
#define  SGTL5000_CHIP_ID 128 

__attribute__((used)) static bool sgtl5000_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case SGTL5000_CHIP_ID:
	case SGTL5000_CHIP_ADCDAC_CTRL:
	case SGTL5000_CHIP_ANA_STATUS:
		return true;
	}

	return false;
}