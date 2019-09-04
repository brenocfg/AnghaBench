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
struct snd_pcm_substream {scalar_t__ stream; TYPE_2__* runtime; struct snd_oxfw* private_data; } ;
struct snd_oxfw_stream_formation {int /*<<< orphan*/  rate; int /*<<< orphan*/  pcm; } ;
struct snd_oxfw {int dummy; } ;
typedef  enum avc_general_plug_dir { ____Placeholder_avc_general_plug_dir } avc_general_plug_dir ;
struct TYPE_3__ {int /*<<< orphan*/  rate_max; int /*<<< orphan*/  rate_min; int /*<<< orphan*/  channels_max; int /*<<< orphan*/  channels_min; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;

/* Variables and functions */
 int AVC_GENERAL_PLUG_DIR_IN ; 
 int AVC_GENERAL_PLUG_DIR_OUT ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int snd_oxfw_stream_get_current_formation (struct snd_oxfw*,int,struct snd_oxfw_stream_formation*) ; 

__attribute__((used)) static int limit_to_current_params(struct snd_pcm_substream *substream)
{
	struct snd_oxfw *oxfw = substream->private_data;
	struct snd_oxfw_stream_formation formation;
	enum avc_general_plug_dir dir;
	int err;

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		dir = AVC_GENERAL_PLUG_DIR_OUT;
	else
		dir = AVC_GENERAL_PLUG_DIR_IN;

	err = snd_oxfw_stream_get_current_formation(oxfw, dir, &formation);
	if (err < 0)
		goto end;

	substream->runtime->hw.channels_min = formation.pcm;
	substream->runtime->hw.channels_max = formation.pcm;
	substream->runtime->hw.rate_min = formation.rate;
	substream->runtime->hw.rate_max = formation.rate;
end:
	return err;
}