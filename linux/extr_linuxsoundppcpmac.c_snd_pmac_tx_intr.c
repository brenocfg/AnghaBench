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
struct snd_pmac {int /*<<< orphan*/  playback; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  snd_pmac_pcm_update (struct snd_pmac*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
snd_pmac_tx_intr(int irq, void *devid)
{
	struct snd_pmac *chip = devid;
	snd_pmac_pcm_update(chip, &chip->playback);
	return IRQ_HANDLED;
}