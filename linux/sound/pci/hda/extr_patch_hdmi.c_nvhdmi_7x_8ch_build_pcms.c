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
struct hdmi_spec {int dummy; } ;
struct hda_pcm {int own_chmap; } ;
struct hda_codec {struct hdmi_spec* spec; } ;

/* Variables and functions */
 struct hda_pcm* get_pcm_rec (struct hdmi_spec*,int /*<<< orphan*/ ) ; 
 int simple_playback_build_pcms (struct hda_codec*) ; 

__attribute__((used)) static int nvhdmi_7x_8ch_build_pcms(struct hda_codec *codec)
{
	struct hdmi_spec *spec = codec->spec;
	int err = simple_playback_build_pcms(codec);
	if (!err) {
		struct hda_pcm *info = get_pcm_rec(spec, 0);
		info->own_chmap = true;
	}
	return err;
}