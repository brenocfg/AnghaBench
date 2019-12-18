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
struct snd_ali {TYPE_1__* card; scalar_t__ spdif_support; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ALI_CHANNELS ; 
 int /*<<< orphan*/  ALI_GLOBAL_CONTROL ; 
 int ALI_PCM_IN_CHANNEL ; 
 int /*<<< orphan*/  ALI_REG (struct snd_ali*,int /*<<< orphan*/ ) ; 
 int ALI_SPDIF_IN_CHANNEL ; 
 int ALI_SPDIF_IN_SUPPORT ; 
 int ALI_SPDIF_OUT_CHANNEL ; 
 int ALI_SPDIF_OUT_CH_ENABLE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int inl (int /*<<< orphan*/ ) ; 
 int snd_ali_alloc_pcm_channel (struct snd_ali*,int) ; 

__attribute__((used)) static int snd_ali_find_free_channel(struct snd_ali * codec, int rec)
{
	int idx;
	int result = -1;

	dev_dbg(codec->card->dev,
		"find_free_channel: for %s\n", rec ? "rec" : "pcm");

	/* recording */
	if (rec) {
		if (codec->spdif_support &&
		    (inl(ALI_REG(codec, ALI_GLOBAL_CONTROL)) &
		     ALI_SPDIF_IN_SUPPORT))
			idx = ALI_SPDIF_IN_CHANNEL;
		else
			idx = ALI_PCM_IN_CHANNEL;

		result = snd_ali_alloc_pcm_channel(codec, idx);
		if (result >= 0)
			return result;
		else {
			dev_err(codec->card->dev,
				"ali_find_free_channel: record channel is busy now.\n");
			return -1;
		}
	}

	/* playback... */
	if (codec->spdif_support &&
	    (inl(ALI_REG(codec, ALI_GLOBAL_CONTROL)) &
	     ALI_SPDIF_OUT_CH_ENABLE)) {
		idx = ALI_SPDIF_OUT_CHANNEL;
		result = snd_ali_alloc_pcm_channel(codec, idx);
		if (result >= 0)
			return result;
		else
			dev_err(codec->card->dev,
				"ali_find_free_channel: S/PDIF out channel is in busy now.\n");
	}

	for (idx = 0; idx < ALI_CHANNELS; idx++) {
		result = snd_ali_alloc_pcm_channel(codec, idx);
		if (result >= 0)
			return result;
	}
	dev_err(codec->card->dev, "ali_find_free_channel: no free channels.\n");
	return -1;
}