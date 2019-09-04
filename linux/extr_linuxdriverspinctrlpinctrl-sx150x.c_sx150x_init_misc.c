#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sx150x_pinctrl {int /*<<< orphan*/  regmap; TYPE_4__* data; } ;
struct TYPE_7__ {int reg_advanced; } ;
struct TYPE_6__ {int reg_advanced; } ;
struct TYPE_8__ {int reg_misc; } ;
struct TYPE_10__ {TYPE_2__ x123; TYPE_1__ x456; TYPE_3__ x789; } ;
struct TYPE_9__ {int model; TYPE_5__ pri; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SX150X_123 130 
#define  SX150X_456 129 
#define  SX150X_789 128 
 int SX150X_789_REG_MISC_AUTOCLEAR_OFF ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sx150x_init_misc(struct sx150x_pinctrl *pctl)
{
	u8 reg, value;

	switch (pctl->data->model) {
	case SX150X_789:
		reg   = pctl->data->pri.x789.reg_misc;
		value = SX150X_789_REG_MISC_AUTOCLEAR_OFF;
		break;
	case SX150X_456:
		reg   = pctl->data->pri.x456.reg_advanced;
		value = 0x00;

		/*
		 * Only SX1506 has RegAdvanced, SX1504/5 are expected
		 * to initialize this offset to zero
		 */
		if (!reg)
			return 0;
		break;
	case SX150X_123:
		reg   = pctl->data->pri.x123.reg_advanced;
		value = 0x00;
		break;
	default:
		WARN(1, "Unknown chip model %d\n", pctl->data->model);
		return -EINVAL;
	}

	return regmap_write(pctl->regmap, reg, value);
}