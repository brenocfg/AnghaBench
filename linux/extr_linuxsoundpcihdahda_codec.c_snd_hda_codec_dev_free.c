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
struct hda_codec {int in_freeing; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  hda_codec_dev (struct hda_codec*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hdac_link_power (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int snd_hda_codec_dev_free(struct snd_device *device)
{
	struct hda_codec *codec = device->device_data;

	codec->in_freeing = 1;
	snd_hdac_device_unregister(&codec->core);
	snd_hdac_link_power(&codec->core, false);
	put_device(hda_codec_dev(codec));
	return 0;
}