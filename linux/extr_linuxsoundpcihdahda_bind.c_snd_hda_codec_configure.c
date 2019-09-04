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
struct hda_codec {int /*<<< orphan*/  core; int /*<<< orphan*/  preset; scalar_t__ probe_id; } ;

/* Variables and functions */
 scalar_t__ HDA_CODEC_ID_GENERIC ; 
 int codec_bind_generic (struct hda_codec*) ; 
 int /*<<< orphan*/  codec_bind_module (struct hda_codec*) ; 
 int /*<<< orphan*/  codec_err (struct hda_codec*,char*) ; 
 scalar_t__ is_generic_config (struct hda_codec*) ; 
 int snd_hdac_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hdac_device_unregister (int /*<<< orphan*/ *) ; 

int snd_hda_codec_configure(struct hda_codec *codec)
{
	int err;

	if (is_generic_config(codec))
		codec->probe_id = HDA_CODEC_ID_GENERIC;
	else
		codec->probe_id = 0;

	err = snd_hdac_device_register(&codec->core);
	if (err < 0)
		return err;

	if (!codec->preset)
		codec_bind_module(codec);
	if (!codec->preset) {
		err = codec_bind_generic(codec);
		if (err < 0) {
			codec_err(codec, "Unable to bind the codec\n");
			goto error;
		}
	}

	return 0;

 error:
	snd_hdac_device_unregister(&codec->core);
	return err;
}