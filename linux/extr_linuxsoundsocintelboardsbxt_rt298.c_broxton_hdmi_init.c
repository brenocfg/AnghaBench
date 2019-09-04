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
struct snd_soc_pcm_runtime {TYPE_1__* card; struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dai {scalar_t__ id; } ;
struct bxt_rt286_private {int /*<<< orphan*/  hdmi_pcm_list; } ;
struct bxt_hdmi_pcm {int /*<<< orphan*/  head; struct snd_soc_dai* codec_dai; scalar_t__ device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BXT_DPCM_AUDIO_HDMI1_PB ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct bxt_hdmi_pcm* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct bxt_rt286_private* snd_soc_card_get_drvdata (TYPE_1__*) ; 

__attribute__((used)) static int broxton_hdmi_init(struct snd_soc_pcm_runtime *rtd)
{
	struct bxt_rt286_private *ctx = snd_soc_card_get_drvdata(rtd->card);
	struct snd_soc_dai *dai = rtd->codec_dai;
	struct bxt_hdmi_pcm *pcm;

	pcm = devm_kzalloc(rtd->card->dev, sizeof(*pcm), GFP_KERNEL);
	if (!pcm)
		return -ENOMEM;

	pcm->device = BXT_DPCM_AUDIO_HDMI1_PB + dai->id;
	pcm->codec_dai = dai;

	list_add_tail(&pcm->head, &ctx->hdmi_pcm_list);

	return 0;
}