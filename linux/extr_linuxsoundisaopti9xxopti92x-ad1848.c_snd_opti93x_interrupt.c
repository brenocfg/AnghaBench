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
struct snd_wss {scalar_t__ capture_substream; scalar_t__ playback_substream; } ;
struct snd_opti9xx {struct snd_wss* codec; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned char OPTi93X_IRQ_CAPTURE ; 
 unsigned char OPTi93X_IRQ_PLAYBACK ; 
 int /*<<< orphan*/  OPTi93X_PORT (struct snd_wss*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPTi9XX_MC_REG (int) ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 unsigned char snd_opti9xx_read (struct snd_opti9xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (scalar_t__) ; 
 int /*<<< orphan*/  snd_wss_overrange (struct snd_wss*) ; 

__attribute__((used)) static irqreturn_t snd_opti93x_interrupt(int irq, void *dev_id)
{
	struct snd_opti9xx *chip = dev_id;
	struct snd_wss *codec = chip->codec;
	unsigned char status;

	if (!codec)
		return IRQ_HANDLED;

	status = snd_opti9xx_read(chip, OPTi9XX_MC_REG(11));
	if ((status & OPTi93X_IRQ_PLAYBACK) && codec->playback_substream)
		snd_pcm_period_elapsed(codec->playback_substream);
	if ((status & OPTi93X_IRQ_CAPTURE) && codec->capture_substream) {
		snd_wss_overrange(codec);
		snd_pcm_period_elapsed(codec->capture_substream);
	}
	outb(0x00, OPTi93X_PORT(codec, STATUS));
	return IRQ_HANDLED;
}