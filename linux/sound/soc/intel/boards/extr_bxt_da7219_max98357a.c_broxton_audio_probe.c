#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {char* platform; } ;
struct snd_soc_acpi_mach {TYPE_3__ mach_params; } ;
struct TYPE_16__ {struct snd_soc_acpi_mach* platform_data; } ;
struct platform_device {TYPE_6__ dev; } ;
struct bxt_card_private {int /*<<< orphan*/  hdmi_pcm_list; } ;
struct TYPE_17__ {char* name; TYPE_2__* cpus; TYPE_1__* codecs; } ;
struct TYPE_15__ {char* name; TYPE_6__* dev; } ;
struct TYPE_13__ {char* dai_name; } ;
struct TYPE_12__ {int /*<<< orphan*/  dai_name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_9__*) ; 
 int /*<<< orphan*/  BXT_DIALOG_CODEC_DAI ; 
 int /*<<< orphan*/  BXT_MAXIM_CODEC_DAI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_4__ broxton_audio_card ; 
 TYPE_9__* broxton_dais ; 
 struct bxt_card_private* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (TYPE_4__*,struct bxt_card_private*) ; 
 int snd_soc_fixup_dai_links_platform_name (TYPE_4__*,char const*) ; 
 scalar_t__ soc_intel_is_cml () ; 
 scalar_t__ soc_intel_is_glk () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int broxton_audio_probe(struct platform_device *pdev)
{
	struct bxt_card_private *ctx;
	struct snd_soc_acpi_mach *mach;
	const char *platform_name;
	int ret;

	ctx = devm_kzalloc(&pdev->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);

	broxton_audio_card.dev = &pdev->dev;
	snd_soc_card_set_drvdata(&broxton_audio_card, ctx);
	if (soc_intel_is_glk()) {
		unsigned int i;

		broxton_audio_card.name = "glkda7219max";
		/* Fixup the SSP entries for geminilake */
		for (i = 0; i < ARRAY_SIZE(broxton_dais); i++) {
			/* MAXIM_CODEC is connected to SSP1. */
			if (!strcmp(broxton_dais[i].codecs->dai_name,
				    BXT_MAXIM_CODEC_DAI)) {
				broxton_dais[i].name = "SSP1-Codec";
				broxton_dais[i].cpus->dai_name = "SSP1 Pin";
			}
			/* DIALOG_CODE is connected to SSP2 */
			else if (!strcmp(broxton_dais[i].codecs->dai_name,
					 BXT_DIALOG_CODEC_DAI)) {
				broxton_dais[i].name = "SSP2-Codec";
				broxton_dais[i].cpus->dai_name = "SSP2 Pin";
			}
		}
	} else if (soc_intel_is_cml()) {
		unsigned int i;

		broxton_audio_card.name = "cmlda7219max";

		for (i = 0; i < ARRAY_SIZE(broxton_dais); i++) {
			/* MAXIM_CODEC is connected to SSP1. */
			if (!strcmp(broxton_dais[i].codecs->dai_name,
					BXT_MAXIM_CODEC_DAI)) {
				broxton_dais[i].name = "SSP1-Codec";
				broxton_dais[i].cpus->dai_name = "SSP1 Pin";
			}
			/* DIALOG_CODEC is connected to SSP0 */
			else if (!strcmp(broxton_dais[i].codecs->dai_name,
					BXT_DIALOG_CODEC_DAI)) {
				broxton_dais[i].name = "SSP0-Codec";
				broxton_dais[i].cpus->dai_name = "SSP0 Pin";
			}
		}
	}

	/* override plaform name, if required */
	mach = (&pdev->dev)->platform_data;
	platform_name = mach->mach_params.platform;

	ret = snd_soc_fixup_dai_links_platform_name(&broxton_audio_card,
						    platform_name);
	if (ret)
		return ret;

	return devm_snd_soc_register_card(&pdev->dev, &broxton_audio_card);
}