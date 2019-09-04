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
#define  STM32_SPDIFRX_CR 134 
#define  STM32_SPDIFRX_CSR 133 
#define  STM32_SPDIFRX_DIR 132 
#define  STM32_SPDIFRX_DR 131 
#define  STM32_SPDIFRX_IFCR 130 
#define  STM32_SPDIFRX_IMR 129 
#define  STM32_SPDIFRX_SR 128 

__attribute__((used)) static bool stm32_spdifrx_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case STM32_SPDIFRX_CR:
	case STM32_SPDIFRX_IMR:
	case STM32_SPDIFRX_SR:
	case STM32_SPDIFRX_IFCR:
	case STM32_SPDIFRX_DR:
	case STM32_SPDIFRX_CSR:
	case STM32_SPDIFRX_DIR:
		return true;
	default:
		return false;
	}
}