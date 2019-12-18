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
struct rt5640_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ RT5640_CHARGE_PUMP ; 
 scalar_t__ RT5640_CHPUMP_INT_REG1 ; 
 int RT5640_CP_FQ1_MASK ; 
 int RT5640_CP_FQ1_SFT ; 
 int RT5640_CP_FQ2_MASK ; 
 int RT5640_CP_FQ2_SFT ; 
 int RT5640_CP_FQ3_MASK ; 
 int RT5640_CP_FQ3_SFT ; 
 int RT5640_CP_FQ_12_KHZ ; 
 int RT5640_CP_FQ_192_KHZ ; 
 int RT5640_DEPOP_AUTO ; 
 scalar_t__ RT5640_DEPOP_M1 ; 
 scalar_t__ RT5640_DEPOP_M2 ; 
 scalar_t__ RT5640_DEPOP_M3 ; 
 int RT5640_DEPOP_MASK ; 
 int RT5640_DIG_DP_EN ; 
 int RT5640_DIG_DP_MASK ; 
 int RT5640_HP_CP_MASK ; 
 int RT5640_HP_CP_PD ; 
 int RT5640_HP_SG_EN ; 
 int RT5640_HP_SG_MASK ; 
 scalar_t__ RT5640_MAMP_INT_REG2 ; 
 int RT5640_PM_HP_HV ; 
 int RT5640_PM_HP_MASK ; 
 scalar_t__ RT5640_PR_BASE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct rt5640_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void rt5640_pmu_depop(struct snd_soc_component *component)
{
	struct rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);

	regmap_update_bits(rt5640->regmap, RT5640_DEPOP_M2,
		RT5640_DEPOP_MASK | RT5640_DIG_DP_MASK,
		RT5640_DEPOP_AUTO | RT5640_DIG_DP_EN);
	regmap_update_bits(rt5640->regmap, RT5640_CHARGE_PUMP,
		RT5640_PM_HP_MASK, RT5640_PM_HP_HV);

	regmap_update_bits(rt5640->regmap, RT5640_DEPOP_M3,
		RT5640_CP_FQ1_MASK | RT5640_CP_FQ2_MASK | RT5640_CP_FQ3_MASK,
		(RT5640_CP_FQ_192_KHZ << RT5640_CP_FQ1_SFT) |
		(RT5640_CP_FQ_12_KHZ << RT5640_CP_FQ2_SFT) |
		(RT5640_CP_FQ_192_KHZ << RT5640_CP_FQ3_SFT));

	regmap_write(rt5640->regmap, RT5640_PR_BASE +
		RT5640_MAMP_INT_REG2, 0x1c00);
	regmap_update_bits(rt5640->regmap, RT5640_DEPOP_M1,
		RT5640_HP_CP_MASK | RT5640_HP_SG_MASK,
		RT5640_HP_CP_PD | RT5640_HP_SG_EN);
	regmap_update_bits(rt5640->regmap, RT5640_PR_BASE +
		RT5640_CHPUMP_INT_REG1, 0x0700, 0x0400);
}