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
struct viadev {int running; } ;
struct via82xx_modem {int dummy; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_2__ {struct viadev* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OFFSET_CONTROL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 132 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  VIADEV_REG (struct viadev*,int /*<<< orphan*/ ) ; 
 unsigned char VIA_REG_CTRL_PAUSE ; 
 unsigned char VIA_REG_CTRL_START ; 
 unsigned char VIA_REG_CTRL_TERMINATE ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 struct via82xx_modem* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_via82xx_channel_reset (struct via82xx_modem*,struct viadev*) ; 

__attribute__((used)) static int snd_via82xx_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct via82xx_modem *chip = snd_pcm_substream_chip(substream);
	struct viadev *viadev = substream->runtime->private_data;
	unsigned char val = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		val |= VIA_REG_CTRL_START;
		viadev->running = 1;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		val = VIA_REG_CTRL_TERMINATE;
		viadev->running = 0;
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		val |= VIA_REG_CTRL_PAUSE;
		viadev->running = 0;
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		viadev->running = 1;
		break;
	default:
		return -EINVAL;
	}
	outb(val, VIADEV_REG(viadev, OFFSET_CONTROL));
	if (cmd == SNDRV_PCM_TRIGGER_STOP)
		snd_via82xx_channel_reset(chip, viadev);
	return 0;
}