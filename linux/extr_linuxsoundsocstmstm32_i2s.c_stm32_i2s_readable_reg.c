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
#define  STM32_I2S_CFG1_REG 136 
#define  STM32_I2S_CFG2_REG 135 
#define  STM32_I2S_CGFR_REG 134 
#define  STM32_I2S_CR1_REG 133 
#define  STM32_I2S_IER_REG 132 
#define  STM32_I2S_IFCR_REG 131 
#define  STM32_I2S_RXDR_REG 130 
#define  STM32_I2S_SR_REG 129 
#define  STM32_I2S_TXDR_REG 128 

__attribute__((used)) static bool stm32_i2s_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case STM32_I2S_CR1_REG:
	case STM32_I2S_CFG1_REG:
	case STM32_I2S_CFG2_REG:
	case STM32_I2S_IER_REG:
	case STM32_I2S_SR_REG:
	case STM32_I2S_IFCR_REG:
	case STM32_I2S_TXDR_REG:
	case STM32_I2S_RXDR_REG:
	case STM32_I2S_CGFR_REG:
		return true;
	default:
		return false;
	}
}