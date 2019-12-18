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
#define  REG_MICFIL_DATACH0 138 
#define  REG_MICFIL_DATACH1 137 
#define  REG_MICFIL_DATACH2 136 
#define  REG_MICFIL_DATACH3 135 
#define  REG_MICFIL_DATACH4 134 
#define  REG_MICFIL_DATACH5 133 
#define  REG_MICFIL_DATACH6 132 
#define  REG_MICFIL_DATACH7 131 
#define  REG_MICFIL_STAT 130 
#define  REG_MICFIL_VAD0_NDATA 129 
#define  REG_MICFIL_VAD0_STAT 128 

__attribute__((used)) static bool fsl_micfil_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case REG_MICFIL_STAT:
	case REG_MICFIL_DATACH0:
	case REG_MICFIL_DATACH1:
	case REG_MICFIL_DATACH2:
	case REG_MICFIL_DATACH3:
	case REG_MICFIL_DATACH4:
	case REG_MICFIL_DATACH5:
	case REG_MICFIL_DATACH6:
	case REG_MICFIL_DATACH7:
	case REG_MICFIL_VAD0_STAT:
	case REG_MICFIL_VAD0_NDATA:
		return true;
	default:
		return false;
	}
}