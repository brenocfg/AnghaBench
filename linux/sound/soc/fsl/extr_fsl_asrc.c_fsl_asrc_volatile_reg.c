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
#define  REG_ASRCFG 138 
#define  REG_ASRDIA 137 
#define  REG_ASRDIB 136 
#define  REG_ASRDIC 135 
#define  REG_ASRDOA 134 
#define  REG_ASRDOB 133 
#define  REG_ASRDOC 132 
#define  REG_ASRFSTA 131 
#define  REG_ASRFSTB 130 
#define  REG_ASRFSTC 129 
#define  REG_ASRSTR 128 

__attribute__((used)) static bool fsl_asrc_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case REG_ASRSTR:
	case REG_ASRDIA:
	case REG_ASRDIB:
	case REG_ASRDIC:
	case REG_ASRDOA:
	case REG_ASRDOB:
	case REG_ASRDOC:
	case REG_ASRFSTA:
	case REG_ASRFSTB:
	case REG_ASRFSTC:
	case REG_ASRCFG:
		return true;
	default:
		return false;
	}
}