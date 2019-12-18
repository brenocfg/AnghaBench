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
struct ssm2602_priv {int /*<<< orphan*/  regmap; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOUT1V_LRHP_BOTH ; 
 int /*<<< orphan*/  ROUT1V_RLHP_BOTH ; 
 int /*<<< orphan*/  SSM2602_LOUT1V ; 
 int /*<<< orphan*/  SSM2602_ROUT1V ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct ssm2602_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssm2602_dapm_widgets ; 
 int /*<<< orphan*/  ssm2602_routes ; 
 int /*<<< orphan*/  ssm2602_snd_controls ; 

__attribute__((used)) static int ssm2602_component_probe(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct ssm2602_priv *ssm2602 = snd_soc_component_get_drvdata(component);
	int ret;

	regmap_update_bits(ssm2602->regmap, SSM2602_LOUT1V,
			    LOUT1V_LRHP_BOTH, LOUT1V_LRHP_BOTH);
	regmap_update_bits(ssm2602->regmap, SSM2602_ROUT1V,
			    ROUT1V_RLHP_BOTH, ROUT1V_RLHP_BOTH);

	ret = snd_soc_add_component_controls(component, ssm2602_snd_controls,
			ARRAY_SIZE(ssm2602_snd_controls));
	if (ret)
		return ret;

	ret = snd_soc_dapm_new_controls(dapm, ssm2602_dapm_widgets,
			ARRAY_SIZE(ssm2602_dapm_widgets));
	if (ret)
		return ret;

	return snd_soc_dapm_add_routes(dapm, ssm2602_routes,
			ARRAY_SIZE(ssm2602_routes));
}