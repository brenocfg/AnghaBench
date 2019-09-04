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
#define  WM2000_REG_ANA_MIC_CTL 150 
#define  WM2000_REG_ANA_VMID_PD_TIME 149 
#define  WM2000_REG_ANA_VMID_PU_TIME 148 
#define  WM2000_REG_ANC_GAIN_CTRL 147 
#define  WM2000_REG_ANC_STAT 146 
#define  WM2000_REG_CAT_FLTR_INDX 145 
#define  WM2000_REG_CAT_GAIN_0 144 
#define  WM2000_REG_ID1 143 
#define  WM2000_REG_ID2 142 
#define  WM2000_REG_IF_CTL 141 
#define  WM2000_REG_MSE_TH1 140 
#define  WM2000_REG_MSE_TH2 139 
#define  WM2000_REG_REVISON 138 
#define  WM2000_REG_SPEECH_CLARITY 137 
#define  WM2000_REG_SPK_CTL 136 
#define  WM2000_REG_SYS_CTL1 135 
#define  WM2000_REG_SYS_CTL2 134 
#define  WM2000_REG_SYS_MODE_CNTRL 133 
#define  WM2000_REG_SYS_START 132 
#define  WM2000_REG_SYS_START0 131 
#define  WM2000_REG_SYS_START1 130 
#define  WM2000_REG_SYS_STATUS 129 
#define  WM2000_REG_SYS_WATCHDOG 128 

__attribute__((used)) static bool wm2000_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case WM2000_REG_SYS_START:
	case WM2000_REG_ANC_GAIN_CTRL:
	case WM2000_REG_MSE_TH1:
	case WM2000_REG_MSE_TH2:
	case WM2000_REG_SPEECH_CLARITY:
	case WM2000_REG_SYS_WATCHDOG:
	case WM2000_REG_ANA_VMID_PD_TIME:
	case WM2000_REG_ANA_VMID_PU_TIME:
	case WM2000_REG_CAT_FLTR_INDX:
	case WM2000_REG_CAT_GAIN_0:
	case WM2000_REG_SYS_STATUS:
	case WM2000_REG_SYS_MODE_CNTRL:
	case WM2000_REG_SYS_START0:
	case WM2000_REG_SYS_START1:
	case WM2000_REG_ID1:
	case WM2000_REG_ID2:
	case WM2000_REG_REVISON:
	case WM2000_REG_SYS_CTL1:
	case WM2000_REG_SYS_CTL2:
	case WM2000_REG_ANC_STAT:
	case WM2000_REG_IF_CTL:
	case WM2000_REG_ANA_MIC_CTL:
	case WM2000_REG_SPK_CTL:
		return true;
	default:
		return false;
	}
}