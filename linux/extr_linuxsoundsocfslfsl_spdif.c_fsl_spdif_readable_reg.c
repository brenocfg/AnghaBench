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
#define  REG_SPDIF_SCR 142 
#define  REG_SPDIF_SIE 141 
#define  REG_SPDIF_SIS 140 
#define  REG_SPDIF_SRCD 139 
#define  REG_SPDIF_SRCSH 138 
#define  REG_SPDIF_SRCSL 137 
#define  REG_SPDIF_SRFM 136 
#define  REG_SPDIF_SRL 135 
#define  REG_SPDIF_SRPC 134 
#define  REG_SPDIF_SRQ 133 
#define  REG_SPDIF_SRR 132 
#define  REG_SPDIF_SRU 131 
#define  REG_SPDIF_STC 130 
#define  REG_SPDIF_STCSCH 129 
#define  REG_SPDIF_STCSCL 128 

__attribute__((used)) static bool fsl_spdif_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case REG_SPDIF_SCR:
	case REG_SPDIF_SRCD:
	case REG_SPDIF_SRPC:
	case REG_SPDIF_SIE:
	case REG_SPDIF_SIS:
	case REG_SPDIF_SRL:
	case REG_SPDIF_SRR:
	case REG_SPDIF_SRCSH:
	case REG_SPDIF_SRCSL:
	case REG_SPDIF_SRU:
	case REG_SPDIF_SRQ:
	case REG_SPDIF_STCSCH:
	case REG_SPDIF_STCSCL:
	case REG_SPDIF_SRFM:
	case REG_SPDIF_STC:
		return true;
	default:
		return false;
	}
}