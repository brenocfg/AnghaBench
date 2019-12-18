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
struct snd_device {struct hda_codec* device_data; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct hda_codec {int in_freeing; TYPE_1__ core; } ;

/* Variables and functions */
 scalar_t__ HDA_DEV_LEGACY ; 
 int /*<<< orphan*/  codec_display_power (struct hda_codec*,int) ; 
 int /*<<< orphan*/  hda_codec_dev (struct hda_codec*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_device_unregister (TYPE_1__*) ; 

__attribute__((used)) static int snd_hda_codec_dev_free(struct snd_device *device)
{
	struct hda_codec *codec = device->device_data;

	codec->in_freeing = 1;
	/*
	 * snd_hda_codec_device_new() is used by legacy HDA and ASoC driver.
	 * We can't unregister ASoC device since it will be unregistered in
	 * snd_hdac_ext_bus_device_remove().
	 */
	if (codec->core.type == HDA_DEV_LEGACY)
		snd_hdac_device_unregister(&codec->core);
	codec_display_power(codec, false);

	/*
	 * In the case of ASoC HD-audio bus, the device refcount is released in
	 * snd_hdac_ext_bus_device_remove() explicitly.
	 */
	if (codec->core.type == HDA_DEV_LEGACY)
		put_device(hda_codec_dev(codec));

	return 0;
}