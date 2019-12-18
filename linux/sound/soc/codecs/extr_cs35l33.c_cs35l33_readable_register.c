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
#define  CS35L33_ADC_CTL 169 
#define  CS35L33_ADSP_CTL 168 
#define  CS35L33_AMP_CTL 167 
#define  CS35L33_BST_CTL1 166 
#define  CS35L33_BST_CTL2 165 
#define  CS35L33_BST_CTL4 164 
#define  CS35L33_BST_PEAK_CTL 163 
#define  CS35L33_CLASSD_CTL 162 
#define  CS35L33_CLK_CTL 161 
#define  CS35L33_DAC_CTL 160 
#define  CS35L33_DEVID_AB 159 
#define  CS35L33_DEVID_CD 158 
#define  CS35L33_DEVID_E 157 
#define  CS35L33_DIAG_CTRL_1 156 
#define  CS35L33_DIAG_CTRL_2 155 
#define  CS35L33_DIAG_LOCK 154 
#define  CS35L33_DIG_VOL_CTL 153 
#define  CS35L33_HG_EN 152 
#define  CS35L33_HG_HEAD 151 
#define  CS35L33_HG_MEMLDO_CTL 150 
#define  CS35L33_HG_REL_RATE 149 
#define  CS35L33_INT_MASK_1 148 
#define  CS35L33_INT_MASK_2 147 
#define  CS35L33_INT_STATUS_1 146 
#define  CS35L33_INT_STATUS_2 145 
#define  CS35L33_LDO_DEL 144 
#define  CS35L33_PROTECT_CTL 143 
#define  CS35L33_PWRCTL1 142 
#define  CS35L33_PWRCTL2 141 
#define  CS35L33_REV_ID 140 
#define  CS35L33_RX_ALIVE 139 
#define  CS35L33_RX_AUD 138 
#define  CS35L33_RX_SPLY 137 
#define  CS35L33_TX_EN1 136 
#define  CS35L33_TX_EN2 135 
#define  CS35L33_TX_EN3 134 
#define  CS35L33_TX_EN4 133 
#define  CS35L33_TX_FLAG 132 
#define  CS35L33_TX_IMON 131 
#define  CS35L33_TX_VBSTMON 130 
#define  CS35L33_TX_VMON 129 
#define  CS35L33_TX_VPMON 128 

__attribute__((used)) static bool cs35l33_readable_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case CS35L33_DEVID_AB:
	case CS35L33_DEVID_CD:
	case CS35L33_DEVID_E:
	case CS35L33_REV_ID:
	case CS35L33_PWRCTL1:
	case CS35L33_PWRCTL2:
	case CS35L33_CLK_CTL:
	case CS35L33_BST_PEAK_CTL:
	case CS35L33_PROTECT_CTL:
	case CS35L33_BST_CTL1:
	case CS35L33_BST_CTL2:
	case CS35L33_ADSP_CTL:
	case CS35L33_ADC_CTL:
	case CS35L33_DAC_CTL:
	case CS35L33_DIG_VOL_CTL:
	case CS35L33_CLASSD_CTL:
	case CS35L33_AMP_CTL:
	case CS35L33_INT_MASK_1:
	case CS35L33_INT_MASK_2:
	case CS35L33_INT_STATUS_1:
	case CS35L33_INT_STATUS_2:
	case CS35L33_DIAG_LOCK:
	case CS35L33_DIAG_CTRL_1:
	case CS35L33_DIAG_CTRL_2:
	case CS35L33_HG_MEMLDO_CTL:
	case CS35L33_HG_REL_RATE:
	case CS35L33_LDO_DEL:
	case CS35L33_HG_HEAD:
	case CS35L33_HG_EN:
	case CS35L33_TX_VMON:
	case CS35L33_TX_IMON:
	case CS35L33_TX_VPMON:
	case CS35L33_TX_VBSTMON:
	case CS35L33_TX_FLAG:
	case CS35L33_TX_EN1:
	case CS35L33_TX_EN2:
	case CS35L33_TX_EN3:
	case CS35L33_TX_EN4:
	case CS35L33_RX_AUD:
	case CS35L33_RX_SPLY:
	case CS35L33_RX_ALIVE:
	case CS35L33_BST_CTL4:
		return true;
	default:
		return false;
	}
}