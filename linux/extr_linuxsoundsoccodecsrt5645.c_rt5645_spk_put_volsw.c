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
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_value {int dummy; } ;
struct rt5645_priv {int /*<<< orphan*/  rcclock_work; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5645_MICBIAS ; 
 int /*<<< orphan*/  RT5645_PWR_CLK25M_MASK ; 
 int /*<<< orphan*/  RT5645_PWR_CLK25M_PU ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct rt5645_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_put_volsw (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static int rt5645_spk_put_volsw(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	struct rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	int ret;

	regmap_update_bits(rt5645->regmap, RT5645_MICBIAS,
		RT5645_PWR_CLK25M_MASK, RT5645_PWR_CLK25M_PU);

	ret = snd_soc_put_volsw(kcontrol, ucontrol);

	mod_delayed_work(system_power_efficient_wq, &rt5645->rcclock_work,
		msecs_to_jiffies(200));

	return ret;
}