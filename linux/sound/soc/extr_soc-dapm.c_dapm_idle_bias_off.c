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
struct snd_soc_dapm_context {int suspend_bias_off; TYPE_1__* card; scalar_t__ idle_bias_off; } ;
struct TYPE_2__ {int /*<<< orphan*/  snd_card; } ;

/* Variables and functions */
#define  SNDRV_CTL_POWER_D3cold 129 
#define  SNDRV_CTL_POWER_D3hot 128 
 int snd_power_get_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dapm_idle_bias_off(struct snd_soc_dapm_context *dapm)
{
	if (dapm->idle_bias_off)
		return true;

	switch (snd_power_get_state(dapm->card->snd_card)) {
	case SNDRV_CTL_POWER_D3hot:
	case SNDRV_CTL_POWER_D3cold:
		return dapm->suspend_bias_off;
	default:
		break;
	}

	return false;
}