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
#define  STM32_SPDIFRX_CR 137 
#define  STM32_SPDIFRX_CSR 136 
#define  STM32_SPDIFRX_DIR 135 
#define  STM32_SPDIFRX_DR 134 
#define  STM32_SPDIFRX_IDR 133 
#define  STM32_SPDIFRX_IFCR 132 
#define  STM32_SPDIFRX_IMR 131 
#define  STM32_SPDIFRX_SIDR 130 
#define  STM32_SPDIFRX_SR 129 
#define  STM32_SPDIFRX_VERR 128 

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
	case STM32_SPDIFRX_VERR:
	case STM32_SPDIFRX_IDR:
	case STM32_SPDIFRX_SIDR:
		return true;
	default:
		return false;
	}
}