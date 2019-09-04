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
struct snd_pcm_substream {int dummy; } ;
struct hda_pcm_stream {int dummy; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int generic_hdmi_playback_pcm_cleanup (struct hda_pcm_stream*,struct hda_codec*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  tegra_hdmi_set_format (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_hdmi_pcm_cleanup(struct hda_pcm_stream *hinfo,
				  struct hda_codec *codec,
				  struct snd_pcm_substream *substream)
{
	/* invalidate the format in the HDMI codec */
	tegra_hdmi_set_format(codec, 0);

	return generic_hdmi_playback_pcm_cleanup(hinfo, codec, substream);
}