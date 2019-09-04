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
struct TYPE_3__ {int max_channels; } ;
struct hdmi_spec {int /*<<< orphan*/  pcm_playback; TYPE_1__ multiout; } ;
struct TYPE_4__ {int /*<<< orphan*/  build_controls; int /*<<< orphan*/  build_pcms; int /*<<< orphan*/  init; } ;
struct hda_codec {TYPE_2__ patch_ops; struct hdmi_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvhdmi_7x_8ch_build_controls ; 
 int /*<<< orphan*/  nvhdmi_7x_8ch_build_pcms ; 
 int /*<<< orphan*/  nvhdmi_7x_init_8ch ; 
 int /*<<< orphan*/  nvhdmi_8ch_7x_set_info_frame_parameters (struct hda_codec*,int) ; 
 int /*<<< orphan*/  nvhdmi_pcm_playback_8ch_7x ; 
 int patch_nvhdmi_2ch (struct hda_codec*) ; 

__attribute__((used)) static int patch_nvhdmi_8ch_7x(struct hda_codec *codec)
{
	struct hdmi_spec *spec;
	int err = patch_nvhdmi_2ch(codec);
	if (err < 0)
		return err;
	spec = codec->spec;
	spec->multiout.max_channels = 8;
	spec->pcm_playback = nvhdmi_pcm_playback_8ch_7x;
	codec->patch_ops.init = nvhdmi_7x_init_8ch;
	codec->patch_ops.build_pcms = nvhdmi_7x_8ch_build_pcms;
	codec->patch_ops.build_controls = nvhdmi_7x_8ch_build_controls;

	/* Initialize the audio infoframe channel mask and checksum to something
	 * valid */
	nvhdmi_8ch_7x_set_info_frame_parameters(codec, 8);

	return 0;
}