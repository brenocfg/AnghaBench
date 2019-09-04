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
#define  MAGICIAN_MIC 129 
#define  MAGICIAN_MIC_EXT 128 
 scalar_t__ magician_hp_switch ; 
 int magician_in_sel ; 
 scalar_t__ magician_spk_switch ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin_unlocked (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin_unlocked (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_lock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_unlock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync_unlocked (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static void magician_ext_control(struct snd_soc_dapm_context *dapm)
{

	snd_soc_dapm_mutex_lock(dapm);

	if (magician_spk_switch)
		snd_soc_dapm_enable_pin_unlocked(dapm, "Speaker");
	else
		snd_soc_dapm_disable_pin_unlocked(dapm, "Speaker");
	if (magician_hp_switch)
		snd_soc_dapm_enable_pin_unlocked(dapm, "Headphone Jack");
	else
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headphone Jack");

	switch (magician_in_sel) {
	case MAGICIAN_MIC:
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headset Mic");
		snd_soc_dapm_enable_pin_unlocked(dapm, "Call Mic");
		break;
	case MAGICIAN_MIC_EXT:
		snd_soc_dapm_disable_pin_unlocked(dapm, "Call Mic");
		snd_soc_dapm_enable_pin_unlocked(dapm, "Headset Mic");
		break;
	}

	snd_soc_dapm_sync_unlocked(dapm);

	snd_soc_dapm_mutex_unlock(dapm);
}