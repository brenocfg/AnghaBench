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
struct cx2072x_priv {int /*<<< orphan*/  regmap; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  CX2072X_AFG_POWER_STATE ; 
 int const SND_SOC_BIAS_OFF ; 
 int SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct cx2072x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cx2072x_set_bias_level(struct snd_soc_component *codec,
				  enum snd_soc_bias_level level)
{
	struct cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);
	const enum snd_soc_bias_level old_level =
		snd_soc_component_get_bias_level(codec);

	if (level == SND_SOC_BIAS_STANDBY && old_level == SND_SOC_BIAS_OFF)
		regmap_write(cx2072x->regmap, CX2072X_AFG_POWER_STATE, 0);
	else if (level == SND_SOC_BIAS_OFF && old_level != SND_SOC_BIAS_OFF)
		regmap_write(cx2072x->regmap, CX2072X_AFG_POWER_STATE, 3);

	return 0;
}