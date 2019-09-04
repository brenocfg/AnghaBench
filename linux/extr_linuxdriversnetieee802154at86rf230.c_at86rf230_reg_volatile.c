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
#define  RG_IRQ_STATUS 135 
#define  RG_PHY_ED_LEVEL 134 
#define  RG_PHY_RSSI 133 
#define  RG_PLL_CF 132 
#define  RG_PLL_DCU 131 
#define  RG_TRX_STATE 130 
#define  RG_TRX_STATUS 129 
#define  RG_VREG_CTRL 128 

__attribute__((used)) static bool
at86rf230_reg_volatile(struct device *dev, unsigned int reg)
{
	/* can be changed during runtime */
	switch (reg) {
	case RG_TRX_STATUS:
	case RG_TRX_STATE:
	case RG_PHY_RSSI:
	case RG_PHY_ED_LEVEL:
	case RG_IRQ_STATUS:
	case RG_VREG_CTRL:
	case RG_PLL_CF:
	case RG_PLL_DCU:
		return true;
	default:
		return false;
	}
}