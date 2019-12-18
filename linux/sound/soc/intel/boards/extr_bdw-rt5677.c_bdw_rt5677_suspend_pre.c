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
struct snd_soc_card {int dummy; } ;
struct bdw_rt5677_priv {scalar_t__ component; } ;

/* Variables and functions */
 struct bdw_rt5677_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (scalar_t__) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 

__attribute__((used)) static int bdw_rt5677_suspend_pre(struct snd_soc_card *card)
{
	struct bdw_rt5677_priv *bdw_rt5677 = snd_soc_card_get_drvdata(card);
	struct snd_soc_dapm_context *dapm;

	if (bdw_rt5677->component) {
		dapm = snd_soc_component_get_dapm(bdw_rt5677->component);
		snd_soc_dapm_disable_pin(dapm, "MICBIAS1");
	}
	return 0;
}