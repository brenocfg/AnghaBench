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
struct snd_soc_dai_link_component {int dummy; } ;
struct snd_soc_dai_link {int /*<<< orphan*/  num_codecs; struct snd_soc_dai_link_component* codecs; int /*<<< orphan*/  name; } ;
struct snd_soc_card {int num_links; int /*<<< orphan*/ * dev; struct snd_soc_dai_link* dai_link; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; TYPE_1__* id_entry; } ;
struct kbl_codec_private {int /*<<< orphan*/  hdmi_pcm_list; } ;
struct TYPE_2__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct snd_soc_dai_link_component*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct kbl_codec_private* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (int /*<<< orphan*/ *,struct snd_soc_card*) ; 
 struct snd_soc_card* kabylake_audio_card ; 
 struct snd_soc_dai_link_component* max98373_ssp0_codec_components ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct kbl_codec_private*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int kabylake_audio_probe(struct platform_device *pdev)
{
	struct kbl_codec_private *ctx;
	struct snd_soc_dai_link *kbl_dai_link;
	struct snd_soc_dai_link_component **codecs;
	int i = 0;

	ctx = devm_kzalloc(&pdev->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);

	kabylake_audio_card =
		(struct snd_soc_card *)pdev->id_entry->driver_data;

	kbl_dai_link = kabylake_audio_card->dai_link;

	/* Update codecs for SSP0 with max98373 codec info */
	if (!strcmp(pdev->name, "kbl_da7219_max98373") ||
		(!strcmp(pdev->name, "kbl_max98373"))) {
		for (i = 0; i < kabylake_audio_card->num_links; ++i) {
			if (strcmp(kbl_dai_link[i].name, "SSP0-Codec"))
				continue;

			codecs = &(kbl_dai_link[i].codecs);
			*codecs = max98373_ssp0_codec_components;
			kbl_dai_link[i].num_codecs =
				ARRAY_SIZE(max98373_ssp0_codec_components);
			break;
		}
	}
	kabylake_audio_card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(kabylake_audio_card, ctx);

	return devm_snd_soc_register_card(&pdev->dev, kabylake_audio_card);
}