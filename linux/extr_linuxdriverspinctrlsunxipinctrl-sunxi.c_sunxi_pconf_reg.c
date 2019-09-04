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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int /*<<< orphan*/  DLEVEL_PINS_MASK ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 131 
#define  PIN_CONFIG_BIAS_PULL_DOWN 130 
#define  PIN_CONFIG_BIAS_PULL_UP 129 
#define  PIN_CONFIG_DRIVE_STRENGTH 128 
 int /*<<< orphan*/  PULL_PINS_MASK ; 
 int /*<<< orphan*/  sunxi_dlevel_offset (unsigned int) ; 
 int /*<<< orphan*/  sunxi_dlevel_reg (unsigned int) ; 
 int /*<<< orphan*/  sunxi_pull_offset (unsigned int) ; 
 int /*<<< orphan*/  sunxi_pull_reg (unsigned int) ; 

__attribute__((used)) static int sunxi_pconf_reg(unsigned pin, enum pin_config_param param,
			   u32 *offset, u32 *shift, u32 *mask)
{
	switch (param) {
	case PIN_CONFIG_DRIVE_STRENGTH:
		*offset = sunxi_dlevel_reg(pin);
		*shift = sunxi_dlevel_offset(pin);
		*mask = DLEVEL_PINS_MASK;
		break;

	case PIN_CONFIG_BIAS_PULL_UP:
	case PIN_CONFIG_BIAS_PULL_DOWN:
	case PIN_CONFIG_BIAS_DISABLE:
		*offset = sunxi_pull_reg(pin);
		*shift = sunxi_pull_offset(pin);
		*mask = PULL_PINS_MASK;
		break;

	default:
		return -ENOTSUPP;
	}

	return 0;
}