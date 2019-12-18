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
struct soc_enum {int dummy; } ;
struct snd_soc_dapm_update {int dummy; } ;
struct snd_soc_dapm_context {struct snd_soc_card* card; } ;
struct snd_soc_card {int /*<<< orphan*/  dapm_mutex; struct snd_soc_dapm_update* update; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_DAPM_CLASS_RUNTIME ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int soc_dapm_mux_update_power (struct snd_soc_card*,struct snd_kcontrol*,int,struct soc_enum*) ; 
 int /*<<< orphan*/  soc_dpcm_runtime_update (struct snd_soc_card*) ; 

int snd_soc_dapm_mux_update_power(struct snd_soc_dapm_context *dapm,
	struct snd_kcontrol *kcontrol, int mux, struct soc_enum *e,
	struct snd_soc_dapm_update *update)
{
	struct snd_soc_card *card = dapm->card;
	int ret;

	mutex_lock_nested(&card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);
	card->update = update;
	ret = soc_dapm_mux_update_power(card, kcontrol, mux, e);
	card->update = NULL;
	mutex_unlock(&card->dapm_mutex);
	if (ret > 0)
		soc_dpcm_runtime_update(card);
	return ret;
}