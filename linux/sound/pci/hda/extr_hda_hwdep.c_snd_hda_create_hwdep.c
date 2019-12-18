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
struct TYPE_4__ {int /*<<< orphan*/  groups; } ;
struct TYPE_3__ {int /*<<< orphan*/  ioctl_compat; int /*<<< orphan*/  ioctl; int /*<<< orphan*/  open; } ;
struct snd_hwdep {char* name; int exclusive; TYPE_2__ dev; TYPE_1__ ops; struct hda_codec* private_data; int /*<<< orphan*/  iface; } ;
struct hda_codec {int addr; struct snd_hwdep* hwdep; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_HWDEP_IFACE_HDA ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_2__*,struct hda_codec*) ; 
 int /*<<< orphan*/  hda_hwdep_ioctl ; 
 int /*<<< orphan*/  hda_hwdep_ioctl_compat ; 
 int /*<<< orphan*/  hda_hwdep_open ; 
 int /*<<< orphan*/  snd_hda_dev_attr_groups ; 
 int snd_hwdep_new (int /*<<< orphan*/ ,char*,int,struct snd_hwdep**) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int snd_hda_create_hwdep(struct hda_codec *codec)
{
	char hwname[16];
	struct snd_hwdep *hwdep;
	int err;

	sprintf(hwname, "HDA Codec %d", codec->addr);
	err = snd_hwdep_new(codec->card, hwname, codec->addr, &hwdep);
	if (err < 0)
		return err;
	codec->hwdep = hwdep;
	sprintf(hwdep->name, "HDA Codec %d", codec->addr);
	hwdep->iface = SNDRV_HWDEP_IFACE_HDA;
	hwdep->private_data = codec;
	hwdep->exclusive = 1;

	hwdep->ops.open = hda_hwdep_open;
	hwdep->ops.ioctl = hda_hwdep_ioctl;
#ifdef CONFIG_COMPAT
	hwdep->ops.ioctl_compat = hda_hwdep_ioctl_compat;
#endif

	/* for sysfs */
	hwdep->dev.groups = snd_hda_dev_attr_groups;
	dev_set_drvdata(&hwdep->dev, codec);

	return 0;
}