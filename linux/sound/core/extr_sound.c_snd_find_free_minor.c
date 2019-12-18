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
struct snd_card {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  SNDRV_DEVICE_TYPE_COMPRESS 135 
#define  SNDRV_DEVICE_TYPE_CONTROL 134 
#define  SNDRV_DEVICE_TYPE_HWDEP 133 
#define  SNDRV_DEVICE_TYPE_PCM_CAPTURE 132 
#define  SNDRV_DEVICE_TYPE_PCM_PLAYBACK 131 
#define  SNDRV_DEVICE_TYPE_RAWMIDI 130 
#define  SNDRV_DEVICE_TYPE_SEQUENCER 129 
#define  SNDRV_DEVICE_TYPE_TIMER 128 
 int SNDRV_MINOR (int /*<<< orphan*/ ,int) ; 
 int SNDRV_OS_MINORS ; 
 scalar_t__ snd_BUG_ON (int) ; 
 scalar_t__* snd_minors ; 

__attribute__((used)) static int snd_find_free_minor(int type, struct snd_card *card, int dev)
{
	int minor;

	switch (type) {
	case SNDRV_DEVICE_TYPE_SEQUENCER:
	case SNDRV_DEVICE_TYPE_TIMER:
		minor = type;
		break;
	case SNDRV_DEVICE_TYPE_CONTROL:
		if (snd_BUG_ON(!card))
			return -EINVAL;
		minor = SNDRV_MINOR(card->number, type);
		break;
	case SNDRV_DEVICE_TYPE_HWDEP:
	case SNDRV_DEVICE_TYPE_RAWMIDI:
	case SNDRV_DEVICE_TYPE_PCM_PLAYBACK:
	case SNDRV_DEVICE_TYPE_PCM_CAPTURE:
	case SNDRV_DEVICE_TYPE_COMPRESS:
		if (snd_BUG_ON(!card))
			return -EINVAL;
		minor = SNDRV_MINOR(card->number, type + dev);
		break;
	default:
		return -EINVAL;
	}
	if (snd_BUG_ON(minor < 0 || minor >= SNDRV_OS_MINORS))
		return -EINVAL;
	if (snd_minors[minor])
		return -EBUSY;
	return minor;
}