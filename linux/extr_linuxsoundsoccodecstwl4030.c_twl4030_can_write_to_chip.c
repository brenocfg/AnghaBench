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
struct twl4030_priv {int /*<<< orphan*/  hsr_enabled; int /*<<< orphan*/  hsl_enabled; int /*<<< orphan*/  carkitr_enabled; int /*<<< orphan*/  carkitl_enabled; int /*<<< orphan*/  predriver_enabled; int /*<<< orphan*/  predrivel_enabled; int /*<<< orphan*/  earpiece_enabled; } ;

/* Variables and functions */
#define  TWL4030_REG_EAR_CTL 133 
#define  TWL4030_REG_HS_GAIN_SET 132 
#define  TWL4030_REG_PRECKL_CTL 131 
#define  TWL4030_REG_PRECKR_CTL 130 
#define  TWL4030_REG_PREDL_CTL 129 
#define  TWL4030_REG_PREDR_CTL 128 

__attribute__((used)) static bool twl4030_can_write_to_chip(struct twl4030_priv *twl4030,
				      unsigned int reg)
{
	bool write_to_reg = false;

	/* Decide if the given register can be written */
	switch (reg) {
	case TWL4030_REG_EAR_CTL:
		if (twl4030->earpiece_enabled)
			write_to_reg = true;
		break;
	case TWL4030_REG_PREDL_CTL:
		if (twl4030->predrivel_enabled)
			write_to_reg = true;
		break;
	case TWL4030_REG_PREDR_CTL:
		if (twl4030->predriver_enabled)
			write_to_reg = true;
		break;
	case TWL4030_REG_PRECKL_CTL:
		if (twl4030->carkitl_enabled)
			write_to_reg = true;
		break;
	case TWL4030_REG_PRECKR_CTL:
		if (twl4030->carkitr_enabled)
			write_to_reg = true;
		break;
	case TWL4030_REG_HS_GAIN_SET:
		if (twl4030->hsl_enabled || twl4030->hsr_enabled)
			write_to_reg = true;
		break;
	default:
		/* All other register can be written */
		write_to_reg = true;
		break;
	}

	return write_to_reg;
}