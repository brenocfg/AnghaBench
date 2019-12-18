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
#define  REG_ESAI_ECR 150 
#define  REG_ESAI_ERDR 149 
#define  REG_ESAI_ESR 148 
#define  REG_ESAI_PCRC 147 
#define  REG_ESAI_PRRC 146 
#define  REG_ESAI_RCCR 145 
#define  REG_ESAI_RCR 144 
#define  REG_ESAI_RFCR 143 
#define  REG_ESAI_RFSR 142 
#define  REG_ESAI_RSMA 141 
#define  REG_ESAI_RSMB 140 
#define  REG_ESAI_RX0 139 
#define  REG_ESAI_RX1 138 
#define  REG_ESAI_RX2 137 
#define  REG_ESAI_RX3 136 
#define  REG_ESAI_SAICR 135 
#define  REG_ESAI_SAISR 134 
#define  REG_ESAI_TCCR 133 
#define  REG_ESAI_TCR 132 
#define  REG_ESAI_TFCR 131 
#define  REG_ESAI_TFSR 130 
#define  REG_ESAI_TSMA 129 
#define  REG_ESAI_TSMB 128 

__attribute__((used)) static bool fsl_esai_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case REG_ESAI_ERDR:
	case REG_ESAI_ECR:
	case REG_ESAI_ESR:
	case REG_ESAI_TFCR:
	case REG_ESAI_TFSR:
	case REG_ESAI_RFCR:
	case REG_ESAI_RFSR:
	case REG_ESAI_RX0:
	case REG_ESAI_RX1:
	case REG_ESAI_RX2:
	case REG_ESAI_RX3:
	case REG_ESAI_SAISR:
	case REG_ESAI_SAICR:
	case REG_ESAI_TCR:
	case REG_ESAI_TCCR:
	case REG_ESAI_RCR:
	case REG_ESAI_RCCR:
	case REG_ESAI_TSMA:
	case REG_ESAI_TSMB:
	case REG_ESAI_RSMA:
	case REG_ESAI_RSMB:
	case REG_ESAI_PRRC:
	case REG_ESAI_PCRC:
		return true;
	default:
		return false;
	}
}