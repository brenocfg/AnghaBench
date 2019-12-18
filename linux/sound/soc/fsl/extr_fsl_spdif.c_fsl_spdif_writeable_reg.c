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
#define  REG_SPDIF_SCR 137 
#define  REG_SPDIF_SIC 136 
#define  REG_SPDIF_SIE 135 
#define  REG_SPDIF_SRCD 134 
#define  REG_SPDIF_SRPC 133 
#define  REG_SPDIF_STC 132 
#define  REG_SPDIF_STCSCH 131 
#define  REG_SPDIF_STCSCL 130 
#define  REG_SPDIF_STL 129 
#define  REG_SPDIF_STR 128 

__attribute__((used)) static bool fsl_spdif_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case REG_SPDIF_SCR:
	case REG_SPDIF_SRCD:
	case REG_SPDIF_SRPC:
	case REG_SPDIF_SIE:
	case REG_SPDIF_SIC:
	case REG_SPDIF_STL:
	case REG_SPDIF_STR:
	case REG_SPDIF_STCSCH:
	case REG_SPDIF_STCSCL:
	case REG_SPDIF_STC:
		return true;
	default:
		return false;
	}
}