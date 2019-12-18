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
struct snd_soc_dapm_context {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  instantiated; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_DAPM_STREAM_NOP ; 
 int dapm_power_widgets (TYPE_1__*,int /*<<< orphan*/ ) ; 

int snd_soc_dapm_sync_unlocked(struct snd_soc_dapm_context *dapm)
{
	/*
	 * Suppress early reports (eg, jacks syncing their state) to avoid
	 * silly DAPM runs during card startup.
	 */
	if (!dapm->card || !dapm->card->instantiated)
		return 0;

	return dapm_power_widgets(dapm->card, SND_SOC_DAPM_STREAM_NOP);
}