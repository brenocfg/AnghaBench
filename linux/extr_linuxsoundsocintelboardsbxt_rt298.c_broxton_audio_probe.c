#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_card {int /*<<< orphan*/ * dev; TYPE_2__* dai_link; int /*<<< orphan*/  name; } ;
struct platform_device {int /*<<< orphan*/  dev; TYPE_1__* id_entry; } ;
struct bxt_rt286_private {int /*<<< orphan*/  hdmi_pcm_list; } ;
struct TYPE_4__ {char* name; char* cpu_dai_name; int /*<<< orphan*/  codec_name; } ;
struct TYPE_3__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PLATFORM_NAME_SIZE ; 
 int /*<<< orphan*/  broxton_rt298_dais ; 
 struct bxt_rt286_private* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (int /*<<< orphan*/ *,struct snd_soc_card*) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct bxt_rt286_private*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int broxton_audio_probe(struct platform_device *pdev)
{
	struct bxt_rt286_private *ctx;
	struct snd_soc_card *card =
			(struct snd_soc_card *)pdev->id_entry->driver_data;
	int i;

	for (i = 0; i < ARRAY_SIZE(broxton_rt298_dais); i++) {
		if (!strncmp(card->dai_link[i].codec_name, "i2c-INT343A:00",
						I2C_NAME_SIZE)) {
			if (!strncmp(card->name, "broxton-rt298",
						PLATFORM_NAME_SIZE)) {
				card->dai_link[i].name = "SSP5-Codec";
				card->dai_link[i].cpu_dai_name = "SSP5 Pin";
			} else if (!strncmp(card->name, "geminilake-rt298",
						PLATFORM_NAME_SIZE)) {
				card->dai_link[i].name = "SSP2-Codec";
				card->dai_link[i].cpu_dai_name = "SSP2 Pin";
			}
		}
	}

	ctx = devm_kzalloc(&pdev->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);

	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, ctx);

	return devm_snd_soc_register_card(&pdev->dev, card);
}