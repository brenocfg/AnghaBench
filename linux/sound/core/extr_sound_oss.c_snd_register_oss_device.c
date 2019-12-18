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
struct snd_minor {int type; int card; int device; struct snd_card* card_ptr; void* private_data; struct file_operations const* f_ops; } ;
struct snd_card {scalar_t__ number; } ;
struct file_operations {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SNDRV_MINOR_OSS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNDRV_MINOR_OSS_AUDIO ; 
 int SNDRV_MINOR_OSS_CARD (int) ; 
 int SNDRV_MINOR_OSS_DEVICE (int) ; 
 scalar_t__ SNDRV_MINOR_OSS_DEVICES ; 
 int /*<<< orphan*/  SNDRV_MINOR_OSS_DMMIDI ; 
 int /*<<< orphan*/  SNDRV_MINOR_OSS_DMMIDI1 ; 
#define  SNDRV_MINOR_OSS_MIDI 130 
#define  SNDRV_MINOR_OSS_MIDI1 129 
#define  SNDRV_MINOR_OSS_PCM 128 
 int /*<<< orphan*/  kfree (struct snd_minor*) ; 
 struct snd_minor* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int register_sound_special_device (struct file_operations const*,int,struct device*) ; 
 struct device* snd_card_get_device_link (struct snd_card*) ; 
 int snd_oss_kernel_minor (int,struct snd_card*,int) ; 
 struct snd_minor** snd_oss_minors ; 
 int /*<<< orphan*/  sound_oss_mutex ; 
 int /*<<< orphan*/  unregister_sound_special (int) ; 

int snd_register_oss_device(int type, struct snd_card *card, int dev,
			    const struct file_operations *f_ops, void *private_data)
{
	int minor = snd_oss_kernel_minor(type, card, dev);
	int minor_unit;
	struct snd_minor *preg;
	int cidx = SNDRV_MINOR_OSS_CARD(minor);
	int track2 = -1;
	int register1 = -1, register2 = -1;
	struct device *carddev = snd_card_get_device_link(card);

	if (card && card->number >= SNDRV_MINOR_OSS_DEVICES)
		return 0; /* ignore silently */
	if (minor < 0)
		return minor;
	preg = kmalloc(sizeof(struct snd_minor), GFP_KERNEL);
	if (preg == NULL)
		return -ENOMEM;
	preg->type = type;
	preg->card = card ? card->number : -1;
	preg->device = dev;
	preg->f_ops = f_ops;
	preg->private_data = private_data;
	preg->card_ptr = card;
	mutex_lock(&sound_oss_mutex);
	snd_oss_minors[minor] = preg;
	minor_unit = SNDRV_MINOR_OSS_DEVICE(minor);
	switch (minor_unit) {
	case SNDRV_MINOR_OSS_PCM:
		track2 = SNDRV_MINOR_OSS(cidx, SNDRV_MINOR_OSS_AUDIO);
		break;
	case SNDRV_MINOR_OSS_MIDI:
		track2 = SNDRV_MINOR_OSS(cidx, SNDRV_MINOR_OSS_DMMIDI);
		break;
	case SNDRV_MINOR_OSS_MIDI1:
		track2 = SNDRV_MINOR_OSS(cidx, SNDRV_MINOR_OSS_DMMIDI1);
		break;
	}
	register1 = register_sound_special_device(f_ops, minor, carddev);
	if (register1 != minor)
		goto __end;
	if (track2 >= 0) {
		register2 = register_sound_special_device(f_ops, track2,
							  carddev);
		if (register2 != track2)
			goto __end;
		snd_oss_minors[track2] = preg;
	}
	mutex_unlock(&sound_oss_mutex);
	return 0;

      __end:
      	if (register2 >= 0)
      		unregister_sound_special(register2);
      	if (register1 >= 0)
      		unregister_sound_special(register1);
	snd_oss_minors[minor] = NULL;
	mutex_unlock(&sound_oss_mutex);
	kfree(preg);
      	return -EBUSY;
}