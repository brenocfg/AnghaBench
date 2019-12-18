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
 int EINVAL ; 
 int SNDRV_MINOR_OSS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNDRV_MINOR_OSS_DMFM ; 
 int /*<<< orphan*/  SNDRV_MINOR_OSS_MIDI ; 
 int /*<<< orphan*/  SNDRV_MINOR_OSS_MIDI1 ; 
 int /*<<< orphan*/  SNDRV_MINOR_OSS_MIXER ; 
 int /*<<< orphan*/  SNDRV_MINOR_OSS_MIXER1 ; 
 int SNDRV_MINOR_OSS_MUSIC ; 
 int /*<<< orphan*/  SNDRV_MINOR_OSS_PCM ; 
 int /*<<< orphan*/  SNDRV_MINOR_OSS_PCM1 ; 
 int SNDRV_MINOR_OSS_SEQUENCER ; 
 int SNDRV_MINOR_OSS_SNDSTAT ; 
#define  SNDRV_OSS_DEVICE_TYPE_DMFM 134 
#define  SNDRV_OSS_DEVICE_TYPE_MIDI 133 
#define  SNDRV_OSS_DEVICE_TYPE_MIXER 132 
#define  SNDRV_OSS_DEVICE_TYPE_MUSIC 131 
#define  SNDRV_OSS_DEVICE_TYPE_PCM 130 
#define  SNDRV_OSS_DEVICE_TYPE_SEQUENCER 129 
#define  SNDRV_OSS_DEVICE_TYPE_SNDSTAT 128 
 int SNDRV_OSS_MINORS ; 
 int /*<<< orphan*/  snd_BUG_ON (int) ; 

__attribute__((used)) static int snd_oss_kernel_minor(int type, struct snd_card *card, int dev)
{
	int minor;

	switch (type) {
	case SNDRV_OSS_DEVICE_TYPE_MIXER:
		if (snd_BUG_ON(!card || dev < 0 || dev > 1))
			return -EINVAL;
		minor = SNDRV_MINOR_OSS(card->number, (dev ? SNDRV_MINOR_OSS_MIXER1 : SNDRV_MINOR_OSS_MIXER));
		break;
	case SNDRV_OSS_DEVICE_TYPE_SEQUENCER:
		minor = SNDRV_MINOR_OSS_SEQUENCER;
		break;
	case SNDRV_OSS_DEVICE_TYPE_MUSIC:
		minor = SNDRV_MINOR_OSS_MUSIC;
		break;
	case SNDRV_OSS_DEVICE_TYPE_PCM:
		if (snd_BUG_ON(!card || dev < 0 || dev > 1))
			return -EINVAL;
		minor = SNDRV_MINOR_OSS(card->number, (dev ? SNDRV_MINOR_OSS_PCM1 : SNDRV_MINOR_OSS_PCM));
		break;
	case SNDRV_OSS_DEVICE_TYPE_MIDI:
		if (snd_BUG_ON(!card || dev < 0 || dev > 1))
			return -EINVAL;
		minor = SNDRV_MINOR_OSS(card->number, (dev ? SNDRV_MINOR_OSS_MIDI1 : SNDRV_MINOR_OSS_MIDI));
		break;
	case SNDRV_OSS_DEVICE_TYPE_DMFM:
		minor = SNDRV_MINOR_OSS(card->number, SNDRV_MINOR_OSS_DMFM);
		break;
	case SNDRV_OSS_DEVICE_TYPE_SNDSTAT:
		minor = SNDRV_MINOR_OSS_SNDSTAT;
		break;
	default:
		return -EINVAL;
	}
	if (minor < 0 || minor >= SNDRV_OSS_MINORS)
		return -EINVAL;
	return minor;
}