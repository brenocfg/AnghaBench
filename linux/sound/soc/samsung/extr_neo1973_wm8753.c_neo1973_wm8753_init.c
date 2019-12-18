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
struct snd_soc_pcm_runtime {struct snd_soc_card* card; } ;
struct snd_soc_card {int /*<<< orphan*/  dapm; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_ignore_suspend (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int neo1973_wm8753_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_card *card = rtd->card;

	/* set endpoints to default off mode */
	snd_soc_dapm_disable_pin(&card->dapm, "GSM Line Out");
	snd_soc_dapm_disable_pin(&card->dapm, "GSM Line In");
	snd_soc_dapm_disable_pin(&card->dapm, "Headset Mic");
	snd_soc_dapm_disable_pin(&card->dapm, "Handset Mic");
	snd_soc_dapm_disable_pin(&card->dapm, "Stereo Out");
	snd_soc_dapm_disable_pin(&card->dapm, "Handset Spk");

	/* allow audio paths from the GSM modem to run during suspend */
	snd_soc_dapm_ignore_suspend(&card->dapm, "GSM Line Out");
	snd_soc_dapm_ignore_suspend(&card->dapm, "GSM Line In");
	snd_soc_dapm_ignore_suspend(&card->dapm, "Headset Mic");
	snd_soc_dapm_ignore_suspend(&card->dapm, "Handset Mic");
	snd_soc_dapm_ignore_suspend(&card->dapm, "Stereo Out");
	snd_soc_dapm_ignore_suspend(&card->dapm, "Handset Spk");

	return 0;
}