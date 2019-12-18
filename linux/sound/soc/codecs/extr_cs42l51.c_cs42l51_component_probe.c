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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct cs42l51_private {scalar_t__ mclk_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS42L51_DAC_CTL ; 
 int CS42L51_DAC_CTL_AMUTE ; 
 int CS42L51_DAC_CTL_DACSZ (int /*<<< orphan*/ ) ; 
 int CS42L51_DAC_CTL_DATA_SEL (int) ; 
 int /*<<< orphan*/  cs42l51_dapm_mclk_widgets ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct cs42l51_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cs42l51_component_probe(struct snd_soc_component *component)
{
	int ret, reg;
	struct snd_soc_dapm_context *dapm;
	struct cs42l51_private *cs42l51;

	cs42l51 = snd_soc_component_get_drvdata(component);
	dapm = snd_soc_component_get_dapm(component);

	if (cs42l51->mclk_handle)
		snd_soc_dapm_new_controls(dapm, cs42l51_dapm_mclk_widgets, 1);

	/*
	 * DAC configuration
	 * - Use signal processor
	 * - auto mute
	 * - vol changes immediate
	 * - no de-emphasize
	 */
	reg = CS42L51_DAC_CTL_DATA_SEL(1)
		| CS42L51_DAC_CTL_AMUTE | CS42L51_DAC_CTL_DACSZ(0);
	ret = snd_soc_component_write(component, CS42L51_DAC_CTL, reg);
	if (ret < 0)
		return ret;

	return 0;
}