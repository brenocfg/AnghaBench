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
#define  REG_MICFIL_CTRL1 141 
#define  REG_MICFIL_CTRL2 140 
#define  REG_MICFIL_DC_CTRL 139 
#define  REG_MICFIL_FIFO_CTRL 138 
#define  REG_MICFIL_FIFO_STAT 137 
#define  REG_MICFIL_OUT_CTRL 136 
#define  REG_MICFIL_OUT_STAT 135 
#define  REG_MICFIL_STAT 134 
#define  REG_MICFIL_VAD0_CTRL1 133 
#define  REG_MICFIL_VAD0_CTRL2 132 
#define  REG_MICFIL_VAD0_NCONFIG 131 
#define  REG_MICFIL_VAD0_SCONFIG 130 
#define  REG_MICFIL_VAD0_STAT 129 
#define  REG_MICFIL_VAD0_ZCD 128 

__attribute__((used)) static bool fsl_micfil_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case REG_MICFIL_CTRL1:
	case REG_MICFIL_CTRL2:
	case REG_MICFIL_STAT:		/* Write 1 to Clear */
	case REG_MICFIL_FIFO_CTRL:
	case REG_MICFIL_FIFO_STAT:	/* Write 1 to Clear */
	case REG_MICFIL_DC_CTRL:
	case REG_MICFIL_OUT_CTRL:
	case REG_MICFIL_OUT_STAT:	/* Write 1 to Clear */
	case REG_MICFIL_VAD0_CTRL1:
	case REG_MICFIL_VAD0_CTRL2:
	case REG_MICFIL_VAD0_STAT:	/* Write 1 to Clear */
	case REG_MICFIL_VAD0_SCONFIG:
	case REG_MICFIL_VAD0_NCONFIG:
	case REG_MICFIL_VAD0_ZCD:
		return true;
	default:
		return false;
	}
}