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
#define  CODEC_RESET 140 
#define  DAC_CLK_CTRL 139 
#define  DAC_INIT_CTRL1 138 
#define  DAC_INIT_CTRL2 137 
#define  DAC_INIT_CTRL3 136 
#define  DAC_PRECHARGE_CTRL 135 
#define  DAC_PWR_CTRL 134 
#define  DAC_SELECT 133 
#define  HPMIX_CTRL 132 
#define  HPOUTL_GAIN_CTRL 131 
#define  HPOUTR_GAIN_CTRL 130 
#define  HPOUT_CTRL 129 
#define  HPOUT_POP_CTRL 128 

__attribute__((used)) static bool rk3328_codec_write_read_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case CODEC_RESET:
	case DAC_INIT_CTRL1:
	case DAC_INIT_CTRL2:
	case DAC_INIT_CTRL3:
	case DAC_PRECHARGE_CTRL:
	case DAC_PWR_CTRL:
	case DAC_CLK_CTRL:
	case HPMIX_CTRL:
	case DAC_SELECT:
	case HPOUT_CTRL:
	case HPOUTL_GAIN_CTRL:
	case HPOUTR_GAIN_CTRL:
	case HPOUT_POP_CTRL:
		return true;
	default:
		return false;
	}
}