#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pm8xxx_pin_data {unsigned int pullup; unsigned int high_z; unsigned int input; unsigned int output_value; unsigned int power_source; unsigned int drive_strength; unsigned int dtest; unsigned int amux; unsigned int aout_level; unsigned int paired; } ;
struct TYPE_4__ {TYPE_1__* pins; } ;
struct pm8xxx_mpp {TYPE_2__ desc; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_3__ {struct pm8xxx_pin_data* drv_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PIN_CONFIG_BIAS_HIGH_IMPEDANCE 137 
#define  PIN_CONFIG_BIAS_PULL_UP 136 
#define  PIN_CONFIG_DRIVE_STRENGTH 135 
#define  PIN_CONFIG_INPUT_ENABLE 134 
#define  PIN_CONFIG_OUTPUT 133 
#define  PIN_CONFIG_POWER_SOURCE 132 
#define  PM8XXX_CONFIG_ALEVEL 131 
#define  PM8XXX_CONFIG_AMUX 130 
#define  PM8XXX_CONFIG_DTEST_SELECTOR 129 
#define  PM8XXX_CONFIG_PAIRED 128 
 unsigned long pinconf_to_config_packed (unsigned int,unsigned int) ; 
 unsigned int pinconf_to_config_param (unsigned long) ; 
 struct pm8xxx_mpp* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int pm8xxx_pin_config_get(struct pinctrl_dev *pctldev,
				 unsigned int offset,
				 unsigned long *config)
{
	struct pm8xxx_mpp *pctrl = pinctrl_dev_get_drvdata(pctldev);
	struct pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;
	unsigned param = pinconf_to_config_param(*config);
	unsigned arg;

	switch (param) {
	case PIN_CONFIG_BIAS_PULL_UP:
		arg = pin->pullup;
		break;
	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		arg = pin->high_z;
		break;
	case PIN_CONFIG_INPUT_ENABLE:
		arg = pin->input;
		break;
	case PIN_CONFIG_OUTPUT:
		arg = pin->output_value;
		break;
	case PIN_CONFIG_POWER_SOURCE:
		arg = pin->power_source;
		break;
	case PIN_CONFIG_DRIVE_STRENGTH:
		arg = pin->drive_strength;
		break;
	case PM8XXX_CONFIG_DTEST_SELECTOR:
		arg = pin->dtest;
		break;
	case PM8XXX_CONFIG_AMUX:
		arg = pin->amux;
		break;
	case PM8XXX_CONFIG_ALEVEL:
		arg = pin->aout_level;
		break;
	case PM8XXX_CONFIG_PAIRED:
		arg = pin->paired;
		break;
	default:
		return -EINVAL;
	}

	*config = pinconf_to_config_packed(param, arg);

	return 0;
}