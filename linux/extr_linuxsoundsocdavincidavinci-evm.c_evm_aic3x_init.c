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
struct snd_soc_pcm_runtime {struct snd_soc_card* card; } ;
struct snd_soc_card {int /*<<< orphan*/  dapm; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic3x_dapm_widgets ; 
 int /*<<< orphan*/  audio_map ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_nc_pin (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_of_parse_audio_routing (struct snd_soc_card*,char*) ; 

__attribute__((used)) static int evm_aic3x_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_card *card = rtd->card;
	struct device_node *np = card->dev->of_node;
	int ret;

	/* Add davinci-evm specific widgets */
	snd_soc_dapm_new_controls(&card->dapm, aic3x_dapm_widgets,
				  ARRAY_SIZE(aic3x_dapm_widgets));

	if (np) {
		ret = snd_soc_of_parse_audio_routing(card, "ti,audio-routing");
		if (ret)
			return ret;
	} else {
		/* Set up davinci-evm specific audio path audio_map */
		snd_soc_dapm_add_routes(&card->dapm, audio_map,
					ARRAY_SIZE(audio_map));
	}

	/* not connected */
	snd_soc_dapm_nc_pin(&card->dapm, "MONO_LOUT");
	snd_soc_dapm_nc_pin(&card->dapm, "HPLCOM");
	snd_soc_dapm_nc_pin(&card->dapm, "HPRCOM");

	return 0;
}