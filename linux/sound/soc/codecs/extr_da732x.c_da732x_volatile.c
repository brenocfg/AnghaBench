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
#define  DA732X_REG_HPL_DAC_OFF_CNTL 129 
#define  DA732X_REG_HPR_DAC_OFF_CNTL 128 

__attribute__((used)) static bool da732x_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case DA732X_REG_HPL_DAC_OFF_CNTL:
	case DA732X_REG_HPR_DAC_OFF_CNTL:
		return true;
	default:
		return false;
	}
}