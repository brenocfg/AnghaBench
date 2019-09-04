#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct pinctrl_dev {int dummy; } ;
struct pcs_function {unsigned int nconfs; TYPE_1__* conf; } ;
struct pcs_device {unsigned int width; unsigned int (* read ) (scalar_t__) ;scalar_t__ base; int /*<<< orphan*/  (* write ) (unsigned int,scalar_t__) ;} ;
struct TYPE_2__ {int param; unsigned int mask; unsigned int enable; unsigned int disable; } ;

/* Variables and functions */
 unsigned int BITS_PER_BYTE ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 135 
#define  PIN_CONFIG_BIAS_PULL_DOWN 134 
#define  PIN_CONFIG_BIAS_PULL_UP 133 
#define  PIN_CONFIG_DRIVE_STRENGTH 132 
#define  PIN_CONFIG_INPUT_SCHMITT 131 
#define  PIN_CONFIG_INPUT_SCHMITT_ENABLE 130 
#define  PIN_CONFIG_LOW_POWER_MODE 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 int /*<<< orphan*/  ffs (unsigned int) ; 
 unsigned int pcs_get_function (struct pinctrl_dev*,unsigned int,struct pcs_function**) ; 
 int /*<<< orphan*/  pcs_pinconf_clear_bias (struct pinctrl_dev*,unsigned int) ; 
 unsigned int pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct pcs_device* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 unsigned int stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (unsigned int,scalar_t__) ; 

__attribute__((used)) static int pcs_pinconf_set(struct pinctrl_dev *pctldev,
				unsigned pin, unsigned long *configs,
				unsigned num_configs)
{
	struct pcs_device *pcs = pinctrl_dev_get_drvdata(pctldev);
	struct pcs_function *func;
	unsigned offset = 0, shift = 0, i, data, ret;
	u32 arg;
	int j;

	ret = pcs_get_function(pctldev, pin, &func);
	if (ret)
		return ret;

	for (j = 0; j < num_configs; j++) {
		for (i = 0; i < func->nconfs; i++) {
			if (pinconf_to_config_param(configs[j])
				!= func->conf[i].param)
				continue;

			offset = pin * (pcs->width / BITS_PER_BYTE);
			data = pcs->read(pcs->base + offset);
			arg = pinconf_to_config_argument(configs[j]);
			switch (func->conf[i].param) {
			/* 2 parameters */
			case PIN_CONFIG_INPUT_SCHMITT:
			case PIN_CONFIG_DRIVE_STRENGTH:
			case PIN_CONFIG_SLEW_RATE:
			case PIN_CONFIG_LOW_POWER_MODE:
				shift = ffs(func->conf[i].mask) - 1;
				data &= ~func->conf[i].mask;
				data |= (arg << shift) & func->conf[i].mask;
				break;
			/* 4 parameters */
			case PIN_CONFIG_BIAS_DISABLE:
				pcs_pinconf_clear_bias(pctldev, pin);
				break;
			case PIN_CONFIG_BIAS_PULL_DOWN:
			case PIN_CONFIG_BIAS_PULL_UP:
				if (arg)
					pcs_pinconf_clear_bias(pctldev, pin);
				/* fall through */
			case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
				data &= ~func->conf[i].mask;
				if (arg)
					data |= func->conf[i].enable;
				else
					data |= func->conf[i].disable;
				break;
			default:
				return -ENOTSUPP;
			}
			pcs->write(data, pcs->base + offset);

			break;
		}
		if (i >= func->nconfs)
			return -ENOTSUPP;
	} /* for each config */

	return 0;
}