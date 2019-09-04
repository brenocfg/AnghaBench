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
struct snd_soc_component {int dummy; } ;
struct rt5645_priv {scalar_t__ codec_type; int hp_on; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ CODEC_TYPE_RT5650 ; 
 int /*<<< orphan*/  RT5645_CHARGE_PUMP ; 
 int /*<<< orphan*/  RT5645_DEPOP_M1 ; 
 int /*<<< orphan*/  RT5645_DEPOP_M2 ; 
 int /*<<< orphan*/  RT5645_DEPOP_M3 ; 
 int RT5645_DEPOP_MAN ; 
 int RT5645_DEPOP_MASK ; 
 int RT5645_HP_CO_EN ; 
 int RT5645_HP_CO_MASK ; 
 scalar_t__ RT5645_HP_DCC_INT1 ; 
 int RT5645_HP_L_SMT_DIS ; 
 int RT5645_HP_L_SMT_MASK ; 
 int RT5645_HP_R_SMT_DIS ; 
 int RT5645_HP_R_SMT_MASK ; 
 int RT5645_HP_SG_DIS ; 
 int RT5645_HP_SG_EN ; 
 int RT5645_HP_SG_MASK ; 
 scalar_t__ RT5645_MAMP_INT_REG2 ; 
 scalar_t__ RT5645_PR_BASE ; 
 int /*<<< orphan*/  RT5645_PWR_ANLG1 ; 
 int RT5645_PWR_FV1 ; 
 int RT5645_PWR_FV2 ; 
 int RT5645_PWR_HA ; 
 int RT5645_PWR_HP_L ; 
 int RT5645_PWR_HP_R ; 
 int RT5645_PWR_HV_L ; 
 int RT5645_PWR_HV_R ; 
 int /*<<< orphan*/  RT5645_PWR_VOL ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct rt5645_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hp_amp_power(struct snd_soc_component *component, int on)
{
	static int hp_amp_power_count;
	struct rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);

	if (on) {
		if (hp_amp_power_count <= 0) {
			if (rt5645->codec_type == CODEC_TYPE_RT5650) {
				snd_soc_component_write(component, RT5645_DEPOP_M2, 0x3100);
				snd_soc_component_write(component, RT5645_CHARGE_PUMP,
					0x0e06);
				snd_soc_component_write(component, RT5645_DEPOP_M1, 0x000d);
				regmap_write(rt5645->regmap, RT5645_PR_BASE +
					RT5645_HP_DCC_INT1, 0x9f01);
				msleep(20);
				snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
					RT5645_HP_CO_MASK, RT5645_HP_CO_EN);
				regmap_write(rt5645->regmap, RT5645_PR_BASE +
					0x3e, 0x7400);
				snd_soc_component_write(component, RT5645_DEPOP_M3, 0x0737);
				regmap_write(rt5645->regmap, RT5645_PR_BASE +
					RT5645_MAMP_INT_REG2, 0xfc00);
				snd_soc_component_write(component, RT5645_DEPOP_M2, 0x1140);
				msleep(90);
				rt5645->hp_on = true;
			} else {
				/* depop parameters */
				snd_soc_component_update_bits(component, RT5645_DEPOP_M2,
					RT5645_DEPOP_MASK, RT5645_DEPOP_MAN);
				snd_soc_component_write(component, RT5645_DEPOP_M1, 0x000d);
				regmap_write(rt5645->regmap, RT5645_PR_BASE +
					RT5645_HP_DCC_INT1, 0x9f01);
				mdelay(150);
				/* headphone amp power on */
				snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
					RT5645_PWR_FV1 | RT5645_PWR_FV2, 0);
				snd_soc_component_update_bits(component, RT5645_PWR_VOL,
					RT5645_PWR_HV_L | RT5645_PWR_HV_R,
					RT5645_PWR_HV_L | RT5645_PWR_HV_R);
				snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
					RT5645_PWR_HP_L | RT5645_PWR_HP_R |
					RT5645_PWR_HA,
					RT5645_PWR_HP_L | RT5645_PWR_HP_R |
					RT5645_PWR_HA);
				mdelay(5);
				snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
					RT5645_PWR_FV1 | RT5645_PWR_FV2,
					RT5645_PWR_FV1 | RT5645_PWR_FV2);

				snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
					RT5645_HP_CO_MASK | RT5645_HP_SG_MASK,
					RT5645_HP_CO_EN | RT5645_HP_SG_EN);
				regmap_write(rt5645->regmap, RT5645_PR_BASE +
					0x14, 0x1aaa);
				regmap_write(rt5645->regmap, RT5645_PR_BASE +
					0x24, 0x0430);
			}
		}
		hp_amp_power_count++;
	} else {
		hp_amp_power_count--;
		if (hp_amp_power_count <= 0) {
			if (rt5645->codec_type == CODEC_TYPE_RT5650) {
				regmap_write(rt5645->regmap, RT5645_PR_BASE +
					0x3e, 0x7400);
				snd_soc_component_write(component, RT5645_DEPOP_M3, 0x0737);
				regmap_write(rt5645->regmap, RT5645_PR_BASE +
					RT5645_MAMP_INT_REG2, 0xfc00);
				snd_soc_component_write(component, RT5645_DEPOP_M2, 0x1140);
				msleep(100);
				snd_soc_component_write(component, RT5645_DEPOP_M1, 0x0001);

			} else {
				snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
					RT5645_HP_SG_MASK |
					RT5645_HP_L_SMT_MASK |
					RT5645_HP_R_SMT_MASK,
					RT5645_HP_SG_DIS |
					RT5645_HP_L_SMT_DIS |
					RT5645_HP_R_SMT_DIS);
				/* headphone amp power down */
				snd_soc_component_write(component, RT5645_DEPOP_M1, 0x0000);
				snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
					RT5645_PWR_HP_L | RT5645_PWR_HP_R |
					RT5645_PWR_HA, 0);
				snd_soc_component_update_bits(component, RT5645_DEPOP_M2,
					RT5645_DEPOP_MASK, 0);
			}
		}
	}
}