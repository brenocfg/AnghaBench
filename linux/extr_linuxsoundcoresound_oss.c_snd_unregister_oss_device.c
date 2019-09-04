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
struct snd_minor {int dummy; } ;
struct snd_card {scalar_t__ number; } ;

/* Variables and functions */
 int ENOENT ; 
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
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_oss_kernel_minor (int,struct snd_card*,int) ; 
 struct snd_minor** snd_oss_minors ; 
 int /*<<< orphan*/  sound_oss_mutex ; 
 int /*<<< orphan*/  unregister_sound_special (int) ; 

int snd_unregister_oss_device(int type, struct snd_card *card, int dev)
{
	int minor = snd_oss_kernel_minor(type, card, dev);
	int cidx = SNDRV_MINOR_OSS_CARD(minor);
	int track2 = -1;
	struct snd_minor *mptr;

	if (card && card->number >= SNDRV_MINOR_OSS_DEVICES)
		return 0;
	if (minor < 0)
		return minor;
	mutex_lock(&sound_oss_mutex);
	mptr = snd_oss_minors[minor];
	if (mptr == NULL) {
		mutex_unlock(&sound_oss_mutex);
		return -ENOENT;
	}
	unregister_sound_special(minor);
	switch (SNDRV_MINOR_OSS_DEVICE(minor)) {
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
	if (track2 >= 0) {
		unregister_sound_special(track2);
		snd_oss_minors[track2] = NULL;
	}
	snd_oss_minors[minor] = NULL;
	mutex_unlock(&sound_oss_mutex);
	kfree(mptr);
	return 0;
}