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
struct zynq_pinctrl {scalar_t__ pctrl_offset; int /*<<< orphan*/  syscon; } ;
struct pinctrl_dev {int dummy; } ;
typedef  enum zynq_io_standards { ____Placeholder_zynq_io_standards } zynq_io_standards ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 133 
#define  PIN_CONFIG_BIAS_HIGH_IMPEDANCE 132 
#define  PIN_CONFIG_BIAS_PULL_UP 131 
#define  PIN_CONFIG_IOSTANDARD 130 
#define  PIN_CONFIG_LOW_POWER_MODE 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 unsigned int ZYNQ_NUM_MIOS ; 
 int ZYNQ_PINCONF_DISABLE_RECVR ; 
 int ZYNQ_PINCONF_PULLUP ; 
 int ZYNQ_PINCONF_SPEED ; 
 int ZYNQ_PINCONF_TRISTATE ; 
 unsigned long pinconf_to_config_packed (unsigned int,unsigned int) ; 
 unsigned int pinconf_to_config_param (unsigned long) ; 
 struct zynq_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int zynq_iostd_hstl ; 
 void* zynq_pinconf_iostd_get (int) ; 

__attribute__((used)) static int zynq_pinconf_cfg_get(struct pinctrl_dev *pctldev,
				unsigned int pin,
				unsigned long *config)
{
	u32 reg;
	int ret;
	unsigned int arg = 0;
	unsigned int param = pinconf_to_config_param(*config);
	struct zynq_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	if (pin >= ZYNQ_NUM_MIOS)
		return -ENOTSUPP;

	ret = regmap_read(pctrl->syscon, pctrl->pctrl_offset + (4 * pin), &reg);
	if (ret)
		return -EIO;

	switch (param) {
	case PIN_CONFIG_BIAS_PULL_UP:
		if (!(reg & ZYNQ_PINCONF_PULLUP))
			return -EINVAL;
		arg = 1;
		break;
	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		if (!(reg & ZYNQ_PINCONF_TRISTATE))
			return -EINVAL;
		arg = 1;
		break;
	case PIN_CONFIG_BIAS_DISABLE:
		if (reg & ZYNQ_PINCONF_PULLUP || reg & ZYNQ_PINCONF_TRISTATE)
			return -EINVAL;
		break;
	case PIN_CONFIG_SLEW_RATE:
		arg = !!(reg & ZYNQ_PINCONF_SPEED);
		break;
	case PIN_CONFIG_LOW_POWER_MODE:
	{
		enum zynq_io_standards iostd = zynq_pinconf_iostd_get(reg);

		if (iostd != zynq_iostd_hstl)
			return -EINVAL;
		if (!(reg & ZYNQ_PINCONF_DISABLE_RECVR))
			return -EINVAL;
		arg = !!(reg & ZYNQ_PINCONF_DISABLE_RECVR);
		break;
	}
	case PIN_CONFIG_IOSTANDARD:
		arg = zynq_pinconf_iostd_get(reg);
		break;
	default:
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, arg);
	return 0;
}