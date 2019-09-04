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
struct snd_pcm_substream {scalar_t__ stream; } ;
struct hdspm {int max_channels_out; int max_channels_in; int /*<<< orphan*/ * capture_buffer; int /*<<< orphan*/ * playback_buffer; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_hdspm_enable_in (struct hdspm*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdspm_enable_out (struct hdspm*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct hdspm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_hdspm_hw_free(struct snd_pcm_substream *substream)
{
	int i;
	struct hdspm *hdspm = snd_pcm_substream_chip(substream);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {

		/* params_channels(params) should be enough,
		   but to get sure in case of error */
		for (i = 0; i < hdspm->max_channels_out; ++i)
			snd_hdspm_enable_out(hdspm, i, 0);

		hdspm->playback_buffer = NULL;
	} else {
		for (i = 0; i < hdspm->max_channels_in; ++i)
			snd_hdspm_enable_in(hdspm, i, 0);

		hdspm->capture_buffer = NULL;

	}

	snd_pcm_lib_free_pages(substream);

	return 0;
}