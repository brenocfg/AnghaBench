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
typedef  int u32 ;
struct owl_padinfo {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int OWL_PINCONF_PULL_DOWN ; 
 int OWL_PINCONF_PULL_HIZ ; 
 int OWL_PINCONF_PULL_HOLD ; 
 int OWL_PINCONF_PULL_UP ; 
#define  PIN_CONFIG_BIAS_BUS_HOLD 132 
#define  PIN_CONFIG_BIAS_HIGH_IMPEDANCE 131 
#define  PIN_CONFIG_BIAS_PULL_DOWN 130 
#define  PIN_CONFIG_BIAS_PULL_UP 129 
#define  PIN_CONFIG_INPUT_SCHMITT_ENABLE 128 

__attribute__((used)) static int owl_pad_pinconf_val2arg(const struct owl_padinfo *padinfo,
				unsigned int param,
				u32 *arg)
{
	switch (param) {
	case PIN_CONFIG_BIAS_BUS_HOLD:
		*arg = *arg == OWL_PINCONF_PULL_HOLD;
		break;
	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		*arg = *arg == OWL_PINCONF_PULL_HIZ;
		break;
	case PIN_CONFIG_BIAS_PULL_DOWN:
		*arg = *arg == OWL_PINCONF_PULL_DOWN;
		break;
	case PIN_CONFIG_BIAS_PULL_UP:
		*arg = *arg == OWL_PINCONF_PULL_UP;
		break;
	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		*arg = *arg == 1;
		break;
	default:
		return -ENOTSUPP;
	}

	return 0;
}