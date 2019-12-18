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
#define  REG_SPDIF_SIS 136 
#define  REG_SPDIF_SRCSH 135 
#define  REG_SPDIF_SRCSL 134 
#define  REG_SPDIF_SRFM 133 
#define  REG_SPDIF_SRL 132 
#define  REG_SPDIF_SRPC 131 
#define  REG_SPDIF_SRQ 130 
#define  REG_SPDIF_SRR 129 
#define  REG_SPDIF_SRU 128 

__attribute__((used)) static bool fsl_spdif_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case REG_SPDIF_SRPC:
	case REG_SPDIF_SIS:
	case REG_SPDIF_SRL:
	case REG_SPDIF_SRR:
	case REG_SPDIF_SRCSH:
	case REG_SPDIF_SRCSL:
	case REG_SPDIF_SRU:
	case REG_SPDIF_SRQ:
	case REG_SPDIF_SRFM:
		return true;
	default:
		return false;
	}
}