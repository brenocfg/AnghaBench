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
struct hda_codec {struct hda_beep* beep; } ;
struct hda_beep {int registered; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  codec_err (struct hda_codec*,char*) ; 
 int /*<<< orphan*/  input_free_device (int /*<<< orphan*/ ) ; 
 int input_register_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hda_beep*) ; 

int snd_hda_register_beep_device(struct hda_codec *codec)
{
	struct hda_beep *beep = codec->beep;
	int err;

	if (!beep || !beep->dev)
		return 0;

	err = input_register_device(beep->dev);
	if (err < 0) {
		codec_err(codec, "hda_beep: unable to register input device\n");
		input_free_device(beep->dev);
		codec->beep = NULL;
		kfree(beep);
		return err;
	}
	beep->registered = true;
	return 0;
}