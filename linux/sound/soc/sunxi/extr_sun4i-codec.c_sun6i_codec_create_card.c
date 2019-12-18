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
struct snd_soc_card {char* name; int fully_routed; int /*<<< orphan*/  num_dapm_widgets; int /*<<< orphan*/  dapm_widgets; struct device* dev; int /*<<< orphan*/  dai_link; int /*<<< orphan*/  num_links; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct snd_soc_card* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 struct snd_soc_card* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int snd_soc_of_parse_audio_routing (struct snd_soc_card*,char*) ; 
 int /*<<< orphan*/  sun4i_codec_create_link (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun6i_codec_card_dapm_widgets ; 

__attribute__((used)) static struct snd_soc_card *sun6i_codec_create_card(struct device *dev)
{
	struct snd_soc_card *card;
	int ret;

	card = devm_kzalloc(dev, sizeof(*card), GFP_KERNEL);
	if (!card)
		return ERR_PTR(-ENOMEM);

	card->dai_link = sun4i_codec_create_link(dev, &card->num_links);
	if (!card->dai_link)
		return ERR_PTR(-ENOMEM);

	card->dev		= dev;
	card->name		= "A31 Audio Codec";
	card->dapm_widgets	= sun6i_codec_card_dapm_widgets;
	card->num_dapm_widgets	= ARRAY_SIZE(sun6i_codec_card_dapm_widgets);
	card->fully_routed	= true;

	ret = snd_soc_of_parse_audio_routing(card, "allwinner,audio-routing");
	if (ret)
		dev_warn(dev, "failed to parse audio-routing: %d\n", ret);

	return card;
}