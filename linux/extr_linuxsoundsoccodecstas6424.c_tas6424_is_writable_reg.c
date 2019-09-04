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
#define  TAS6424_AC_DIAG_CTRL1 147 
#define  TAS6424_CBC_STAT 146 
#define  TAS6424_CH1_VOL_CTRL 145 
#define  TAS6424_CH2_VOL_CTRL 144 
#define  TAS6424_CH3_VOL_CTRL 143 
#define  TAS6424_CH4_VOL_CTRL 142 
#define  TAS6424_CH_STATE_CTRL 141 
#define  TAS6424_CLIP_CTRL 140 
#define  TAS6424_CLIP_WARN 139 
#define  TAS6424_CLIP_WINDOW 138 
#define  TAS6424_DC_DIAG_CTRL1 137 
#define  TAS6424_DC_DIAG_CTRL2 136 
#define  TAS6424_DC_DIAG_CTRL3 135 
#define  TAS6424_MISC_CTRL1 134 
#define  TAS6424_MISC_CTRL2 133 
#define  TAS6424_MISC_CTRL3 132 
#define  TAS6424_MISC_CTRL4 131 
#define  TAS6424_MODE_CTRL 130 
#define  TAS6424_PIN_CTRL 129 
#define  TAS6424_SAP_CTRL 128 

__attribute__((used)) static bool tas6424_is_writable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case TAS6424_MODE_CTRL:
	case TAS6424_MISC_CTRL1:
	case TAS6424_MISC_CTRL2:
	case TAS6424_SAP_CTRL:
	case TAS6424_CH_STATE_CTRL:
	case TAS6424_CH1_VOL_CTRL:
	case TAS6424_CH2_VOL_CTRL:
	case TAS6424_CH3_VOL_CTRL:
	case TAS6424_CH4_VOL_CTRL:
	case TAS6424_DC_DIAG_CTRL1:
	case TAS6424_DC_DIAG_CTRL2:
	case TAS6424_DC_DIAG_CTRL3:
	case TAS6424_PIN_CTRL:
	case TAS6424_AC_DIAG_CTRL1:
	case TAS6424_MISC_CTRL3:
	case TAS6424_CLIP_CTRL:
	case TAS6424_CLIP_WINDOW:
	case TAS6424_CLIP_WARN:
	case TAS6424_CBC_STAT:
	case TAS6424_MISC_CTRL4:
		return true;
	default:
		return false;
	}
}