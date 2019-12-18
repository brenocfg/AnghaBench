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
#define  REG_MICFIL_CTRL1 150 
#define  REG_MICFIL_CTRL2 149 
#define  REG_MICFIL_DATACH0 148 
#define  REG_MICFIL_DATACH1 147 
#define  REG_MICFIL_DATACH2 146 
#define  REG_MICFIL_DATACH3 145 
#define  REG_MICFIL_DATACH4 144 
#define  REG_MICFIL_DATACH5 143 
#define  REG_MICFIL_DATACH6 142 
#define  REG_MICFIL_DATACH7 141 
#define  REG_MICFIL_DC_CTRL 140 
#define  REG_MICFIL_FIFO_CTRL 139 
#define  REG_MICFIL_FIFO_STAT 138 
#define  REG_MICFIL_OUT_CTRL 137 
#define  REG_MICFIL_OUT_STAT 136 
#define  REG_MICFIL_STAT 135 
#define  REG_MICFIL_VAD0_CTRL1 134 
#define  REG_MICFIL_VAD0_CTRL2 133 
#define  REG_MICFIL_VAD0_NCONFIG 132 
#define  REG_MICFIL_VAD0_NDATA 131 
#define  REG_MICFIL_VAD0_SCONFIG 130 
#define  REG_MICFIL_VAD0_STAT 129 
#define  REG_MICFIL_VAD0_ZCD 128 

__attribute__((used)) static bool fsl_micfil_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case REG_MICFIL_CTRL1:
	case REG_MICFIL_CTRL2:
	case REG_MICFIL_STAT:
	case REG_MICFIL_FIFO_CTRL:
	case REG_MICFIL_FIFO_STAT:
	case REG_MICFIL_DATACH0:
	case REG_MICFIL_DATACH1:
	case REG_MICFIL_DATACH2:
	case REG_MICFIL_DATACH3:
	case REG_MICFIL_DATACH4:
	case REG_MICFIL_DATACH5:
	case REG_MICFIL_DATACH6:
	case REG_MICFIL_DATACH7:
	case REG_MICFIL_DC_CTRL:
	case REG_MICFIL_OUT_CTRL:
	case REG_MICFIL_OUT_STAT:
	case REG_MICFIL_VAD0_CTRL1:
	case REG_MICFIL_VAD0_CTRL2:
	case REG_MICFIL_VAD0_STAT:
	case REG_MICFIL_VAD0_SCONFIG:
	case REG_MICFIL_VAD0_NCONFIG:
	case REG_MICFIL_VAD0_NDATA:
	case REG_MICFIL_VAD0_ZCD:
		return true;
	default:
		return false;
	}
}