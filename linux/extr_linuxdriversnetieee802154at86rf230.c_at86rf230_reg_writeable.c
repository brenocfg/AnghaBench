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
#define  RG_ANT_DIV 163 
#define  RG_BATMON 162 
#define  RG_CCA_THRES 161 
#define  RG_CSMA_BE 160 
#define  RG_CSMA_SEED_0 159 
#define  RG_CSMA_SEED_1 158 
#define  RG_FTN_CTRL 157 
#define  RG_IEEE_ADDR_0 156 
#define  RG_IEEE_ADDR_1 155 
#define  RG_IEEE_ADDR_2 154 
#define  RG_IEEE_ADDR_3 153 
#define  RG_IEEE_ADDR_4 152 
#define  RG_IEEE_ADDR_5 151 
#define  RG_IEEE_ADDR_6 150 
#define  RG_IEEE_ADDR_7 149 
#define  RG_IRQ_MASK 148 
#define  RG_PAN_ID_0 147 
#define  RG_PAN_ID_1 146 
#define  RG_PHY_CC_CCA 145 
#define  RG_PHY_ED_LEVEL 144 
#define  RG_PHY_TX_PWR 143 
#define  RG_PLL_CF 142 
#define  RG_PLL_DCU 141 
#define  RG_RX_CTRL 140 
#define  RG_RX_SYN 139 
#define  RG_SFD_VALUE 138 
#define  RG_SHORT_ADDR_0 137 
#define  RG_SHORT_ADDR_1 136 
#define  RG_TRX_CTRL_0 135 
#define  RG_TRX_CTRL_1 134 
#define  RG_TRX_CTRL_2 133 
#define  RG_TRX_STATE 132 
#define  RG_VREG_CTRL 131 
#define  RG_XAH_CTRL_0 130 
#define  RG_XAH_CTRL_1 129 
#define  RG_XOSC_CTRL 128 

__attribute__((used)) static bool
at86rf230_reg_writeable(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case RG_TRX_STATE:
	case RG_TRX_CTRL_0:
	case RG_TRX_CTRL_1:
	case RG_PHY_TX_PWR:
	case RG_PHY_ED_LEVEL:
	case RG_PHY_CC_CCA:
	case RG_CCA_THRES:
	case RG_RX_CTRL:
	case RG_SFD_VALUE:
	case RG_TRX_CTRL_2:
	case RG_ANT_DIV:
	case RG_IRQ_MASK:
	case RG_VREG_CTRL:
	case RG_BATMON:
	case RG_XOSC_CTRL:
	case RG_RX_SYN:
	case RG_XAH_CTRL_1:
	case RG_FTN_CTRL:
	case RG_PLL_CF:
	case RG_PLL_DCU:
	case RG_SHORT_ADDR_0:
	case RG_SHORT_ADDR_1:
	case RG_PAN_ID_0:
	case RG_PAN_ID_1:
	case RG_IEEE_ADDR_0:
	case RG_IEEE_ADDR_1:
	case RG_IEEE_ADDR_2:
	case RG_IEEE_ADDR_3:
	case RG_IEEE_ADDR_4:
	case RG_IEEE_ADDR_5:
	case RG_IEEE_ADDR_6:
	case RG_IEEE_ADDR_7:
	case RG_XAH_CTRL_0:
	case RG_CSMA_SEED_0:
	case RG_CSMA_SEED_1:
	case RG_CSMA_BE:
		return true;
	default:
		return false;
	}
}