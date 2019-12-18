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
struct hda_codec {scalar_t__ probe_id; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ HDA_CODEC_ID_GENERIC ; 
 scalar_t__ HDA_CODEC_ID_GENERIC_HDMI ; 
 scalar_t__ codec_probed (struct hda_codec*) ; 
 scalar_t__ is_likely_hdmi_codec (struct hda_codec*) ; 
 int /*<<< orphan*/  request_codec_module (struct hda_codec*) ; 

__attribute__((used)) static int codec_bind_generic(struct hda_codec *codec)
{
	if (codec->probe_id)
		return -ENODEV;

	if (is_likely_hdmi_codec(codec)) {
		codec->probe_id = HDA_CODEC_ID_GENERIC_HDMI;
		request_codec_module(codec);
		if (codec_probed(codec))
			return 0;
	}

	codec->probe_id = HDA_CODEC_ID_GENERIC;
	request_codec_module(codec);
	if (codec_probed(codec))
		return 0;
	return -ENODEV;
}