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
typedef  int /*<<< orphan*/  u32 ;
struct owl_padinfo {TYPE_1__* st; TYPE_2__* pullctl; } ;
struct TYPE_4__ {int /*<<< orphan*/  width; int /*<<< orphan*/  shift; int /*<<< orphan*/  reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  width; int /*<<< orphan*/  shift; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_BUS_HOLD 132 
#define  PIN_CONFIG_BIAS_HIGH_IMPEDANCE 131 
#define  PIN_CONFIG_BIAS_PULL_DOWN 130 
#define  PIN_CONFIG_BIAS_PULL_UP 129 
#define  PIN_CONFIG_INPUT_SCHMITT_ENABLE 128 

__attribute__((used)) static int owl_pad_pinconf_reg(const struct owl_padinfo *info,
				unsigned int param,
				u32 *reg,
				u32 *bit,
				u32 *width)
{
	switch (param) {
	case PIN_CONFIG_BIAS_BUS_HOLD:
	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
	case PIN_CONFIG_BIAS_PULL_DOWN:
	case PIN_CONFIG_BIAS_PULL_UP:
		if (!info->pullctl)
			return -EINVAL;
		*reg = info->pullctl->reg;
		*bit = info->pullctl->shift;
		*width = info->pullctl->width;
		break;
	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		if (!info->st)
			return -EINVAL;
		*reg = info->st->reg;
		*bit = info->st->shift;
		*width = info->st->width;
		break;
	default:
		return -ENOTSUPP;
	}

	return 0;
}