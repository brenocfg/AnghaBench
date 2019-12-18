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
#define  STM_SAI_CLRFR_REGX 137 
#define  STM_SAI_CR1_REGX 136 
#define  STM_SAI_CR2_REGX 135 
#define  STM_SAI_DR_REGX 134 
#define  STM_SAI_FRCR_REGX 133 
#define  STM_SAI_IMR_REGX 132 
#define  STM_SAI_PDMCR_REGX 131 
#define  STM_SAI_PDMLY_REGX 130 
#define  STM_SAI_SLOTR_REGX 129 
#define  STM_SAI_SR_REGX 128 

__attribute__((used)) static bool stm32_sai_sub_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case STM_SAI_CR1_REGX:
	case STM_SAI_CR2_REGX:
	case STM_SAI_FRCR_REGX:
	case STM_SAI_SLOTR_REGX:
	case STM_SAI_IMR_REGX:
	case STM_SAI_SR_REGX:
	case STM_SAI_CLRFR_REGX:
	case STM_SAI_DR_REGX:
	case STM_SAI_PDMCR_REGX:
	case STM_SAI_PDMLY_REGX:
		return true;
	default:
		return false;
	}
}