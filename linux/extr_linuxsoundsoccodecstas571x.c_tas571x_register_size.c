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
struct tas571x_private {TYPE_1__* chip; } ;
struct TYPE_2__ {int vol_reg_size; } ;

/* Variables and functions */
#define  TAS5717_CH1_LEFT_CH_MIX_REG 137 
#define  TAS5717_CH1_RIGHT_CH_MIX_REG 136 
#define  TAS5717_CH2_LEFT_CH_MIX_REG 135 
#define  TAS5717_CH2_RIGHT_CH_MIX_REG 134 
#define  TAS571X_CH1_VOL_REG 133 
#define  TAS571X_CH2_VOL_REG 132 
#define  TAS571X_CH4_SRC_SELECT_REG 131 
#define  TAS571X_INPUT_MUX_REG 130 
#define  TAS571X_MVOL_REG 129 
#define  TAS571X_PWM_MUX_REG 128 

__attribute__((used)) static int tas571x_register_size(struct tas571x_private *priv, unsigned int reg)
{
	switch (reg) {
	case TAS571X_MVOL_REG:
	case TAS571X_CH1_VOL_REG:
	case TAS571X_CH2_VOL_REG:
		return priv->chip->vol_reg_size;
	case TAS571X_INPUT_MUX_REG:
	case TAS571X_CH4_SRC_SELECT_REG:
	case TAS571X_PWM_MUX_REG:
	case TAS5717_CH1_RIGHT_CH_MIX_REG:
	case TAS5717_CH1_LEFT_CH_MIX_REG:
	case TAS5717_CH2_LEFT_CH_MIX_REG:
	case TAS5717_CH2_RIGHT_CH_MIX_REG:
		return 4;
	default:
		return 1;
	}
}