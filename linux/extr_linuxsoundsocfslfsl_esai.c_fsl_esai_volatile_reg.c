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
#define  REG_ESAI_ERDR 136 
#define  REG_ESAI_ESR 135 
#define  REG_ESAI_RFSR 134 
#define  REG_ESAI_RX0 133 
#define  REG_ESAI_RX1 132 
#define  REG_ESAI_RX2 131 
#define  REG_ESAI_RX3 130 
#define  REG_ESAI_SAISR 129 
#define  REG_ESAI_TFSR 128 

__attribute__((used)) static bool fsl_esai_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case REG_ESAI_ERDR:
	case REG_ESAI_ESR:
	case REG_ESAI_TFSR:
	case REG_ESAI_RFSR:
	case REG_ESAI_RX0:
	case REG_ESAI_RX1:
	case REG_ESAI_RX2:
	case REG_ESAI_RX3:
	case REG_ESAI_SAISR:
		return true;
	default:
		return false;
	}
}