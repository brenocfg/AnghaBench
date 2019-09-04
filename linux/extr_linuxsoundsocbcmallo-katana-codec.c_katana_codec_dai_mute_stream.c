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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {TYPE_1__* card; } ;
struct katana_codec_priv {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KATANA_CODEC_MUTE_STREAM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct katana_codec_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

int katana_codec_dai_mute_stream(struct snd_soc_dai *dai, int mute,
						int stream)
{
	struct snd_soc_component *component = dai->component;
	struct katana_codec_priv *katana_codec =
		snd_soc_component_get_drvdata(component);
	int ret = 0;

	ret = regmap_write(katana_codec->regmap, KATANA_CODEC_MUTE_STREAM,
				mute);
	if (ret != 0) {
		dev_err(component->card->dev, "Failed to set mute: %d\n", ret);
		return ret;
	}
	return ret;
}