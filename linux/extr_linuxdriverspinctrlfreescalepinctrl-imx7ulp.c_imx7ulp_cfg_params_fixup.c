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
 int /*<<< orphan*/  BM_LK_ENABLED ; 
 int /*<<< orphan*/  BM_PULL_ENABLED ; 
 int PIN_CONFIG_BIAS_PULL_DOWN ; 
 int PIN_CONFIG_BIAS_PULL_UP ; 
 int /*<<< orphan*/  pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 

__attribute__((used)) static void imx7ulp_cfg_params_fixup(unsigned long *configs,
				    unsigned int num_configs,
				    u32 *raw_config)
{
	enum pin_config_param param;
	u32 param_val;
	int i;

	/* lock field disabled */
	*raw_config &= ~BM_LK_ENABLED;

	for (i = 0; i < num_configs; i++) {
		param = pinconf_to_config_param(configs[i]);
		param_val = pinconf_to_config_argument(configs[i]);

		if ((param == PIN_CONFIG_BIAS_PULL_UP) ||
		    (param == PIN_CONFIG_BIAS_PULL_DOWN)) {
			/* pull enabled */
			*raw_config |= BM_PULL_ENABLED;

			return;
		}
	}
}