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
struct snd_device {struct hda_codec* device_data; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hda_detach_beep_device (struct hda_codec*) ; 

__attribute__((used)) static int snd_hda_codec_dev_disconnect(struct snd_device *device)
{
	struct hda_codec *codec = device->device_data;

	snd_hda_detach_beep_device(codec);
	return 0;
}