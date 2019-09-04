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
struct hda_codec {struct hda_codec* wcaps; struct hda_codec* modelname; int /*<<< orphan*/  core; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct hda_codec* dev_to_hda_codec (struct device*) ; 
 int /*<<< orphan*/  free_init_pincfgs (struct hda_codec*) ; 
 int /*<<< orphan*/  kfree (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_sysfs_clear (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hdac_device_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_hda_codec_dev_release(struct device *dev)
{
	struct hda_codec *codec = dev_to_hda_codec(dev);

	free_init_pincfgs(codec);
	snd_hdac_device_exit(&codec->core);
	snd_hda_sysfs_clear(codec);
	kfree(codec->modelname);
	kfree(codec->wcaps);
	kfree(codec);
}