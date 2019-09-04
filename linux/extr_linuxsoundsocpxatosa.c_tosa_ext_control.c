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

/* Variables and functions */
#define  TOSA_HEADSET 130 
#define  TOSA_HP 129 
#define  TOSA_MIC_INT 128 
 scalar_t__ TOSA_SPK_ON ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin_unlocked (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin_unlocked (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_lock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_unlock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync_unlocked (struct snd_soc_dapm_context*) ; 
 int tosa_jack_func ; 
 scalar_t__ tosa_spk_func ; 

__attribute__((used)) static void tosa_ext_control(struct snd_soc_dapm_context *dapm)
{

	snd_soc_dapm_mutex_lock(dapm);

	/* set up jack connection */
	switch (tosa_jack_func) {
	case TOSA_HP:
		snd_soc_dapm_disable_pin_unlocked(dapm, "Mic (Internal)");
		snd_soc_dapm_enable_pin_unlocked(dapm, "Headphone Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headset Jack");
		break;
	case TOSA_MIC_INT:
		snd_soc_dapm_enable_pin_unlocked(dapm, "Mic (Internal)");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headphone Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headset Jack");
		break;
	case TOSA_HEADSET:
		snd_soc_dapm_disable_pin_unlocked(dapm, "Mic (Internal)");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headphone Jack");
		snd_soc_dapm_enable_pin_unlocked(dapm, "Headset Jack");
		break;
	}

	if (tosa_spk_func == TOSA_SPK_ON)
		snd_soc_dapm_enable_pin_unlocked(dapm, "Speaker");
	else
		snd_soc_dapm_disable_pin_unlocked(dapm, "Speaker");

	snd_soc_dapm_sync_unlocked(dapm);

	snd_soc_dapm_mutex_unlock(dapm);
}