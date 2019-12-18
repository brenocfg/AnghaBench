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
struct snd_soc_dai {struct hdmi_codec_daifmt* playback_dma_data; } ;
struct hdmi_codec_daifmt {int /*<<< orphan*/  fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_SPDIF ; 
 int hdmi_dai_probe (struct snd_soc_dai*) ; 

__attribute__((used)) static int hdmi_dai_spdif_probe(struct snd_soc_dai *dai)
{
	struct hdmi_codec_daifmt *cf = dai->playback_dma_data;
	int ret;

	ret = hdmi_dai_probe(dai);
	if (ret)
		return ret;

	cf = dai->playback_dma_data;
	cf->fmt = HDMI_SPDIF;

	return 0;
}