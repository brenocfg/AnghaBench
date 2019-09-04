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
struct TYPE_2__ {int /*<<< orphan*/  cleanup; int /*<<< orphan*/  prepare; } ;
struct hda_pcm_stream {TYPE_1__ ops; } ;
struct hda_pcm {struct hda_pcm_stream* stream; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HDA_PCM_TYPE_HDMI ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int generic_hdmi_build_pcms (struct hda_codec*) ; 
 struct hda_pcm* hda_find_pcm_by_type (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_hdmi_pcm_cleanup ; 
 int /*<<< orphan*/  tegra_hdmi_pcm_prepare ; 

__attribute__((used)) static int tegra_hdmi_build_pcms(struct hda_codec *codec)
{
	struct hda_pcm_stream *stream;
	struct hda_pcm *pcm;
	int err;

	err = generic_hdmi_build_pcms(codec);
	if (err < 0)
		return err;

	pcm = hda_find_pcm_by_type(codec, HDA_PCM_TYPE_HDMI);
	if (!pcm)
		return -ENODEV;

	/*
	 * Override ->prepare() and ->cleanup() operations to notify the HDMI
	 * codec about format changes.
	 */
	stream = &pcm->stream[SNDRV_PCM_STREAM_PLAYBACK];
	stream->ops.prepare = tegra_hdmi_pcm_prepare;
	stream->ops.cleanup = tegra_hdmi_pcm_cleanup;

	return 0;
}