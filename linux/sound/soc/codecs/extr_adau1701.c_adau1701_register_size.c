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
#define  ADAU1701_AUXNPOW 135 
#define  ADAU1701_DACSET 134 
#define  ADAU1701_DSPCTRL 133 
#define  ADAU1701_OSCIPOW 132 
#define  ADAU1701_PINCONF_0 131 
#define  ADAU1701_PINCONF_1 130 
#define  ADAU1701_SERICTL 129 
#define  ADAU1701_SEROCTL 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 

__attribute__((used)) static unsigned int adau1701_register_size(struct device *dev,
		unsigned int reg)
{
	switch (reg) {
	case ADAU1701_PINCONF_0:
	case ADAU1701_PINCONF_1:
		return 3;
	case ADAU1701_DSPCTRL:
	case ADAU1701_SEROCTL:
	case ADAU1701_AUXNPOW:
	case ADAU1701_OSCIPOW:
	case ADAU1701_DACSET:
		return 2;
	case ADAU1701_SERICTL:
		return 1;
	}

	dev_err(dev, "Unsupported register address: %d\n", reg);
	return 0;
}