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
struct snd_opl3 {int dummy; } ;
struct snd_es1688 {scalar_t__ mpu_port; TYPE_1__* pcm; int /*<<< orphan*/  dma8; int /*<<< orphan*/  irq; int /*<<< orphan*/  port; } ;
struct snd_card {int /*<<< orphan*/  dev; int /*<<< orphan*/  longname; int /*<<< orphan*/  shortname; int /*<<< orphan*/  driver; struct snd_es1688* private_data; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPU401_HW_ES1688 ; 
 int /*<<< orphan*/  OPL3_HW_OPL3 ; 
 scalar_t__ SNDRV_AUTO_IRQ ; 
 scalar_t__ SNDRV_AUTO_PORT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__* fm_port ; 
 scalar_t__* mpu_irq ; 
 scalar_t__* port ; 
 int snd_card_register (struct snd_card*) ; 
 int snd_es1688_mixer (struct snd_card*,struct snd_es1688*) ; 
 int snd_es1688_pcm (struct snd_card*,struct snd_es1688*,int /*<<< orphan*/ ) ; 
 int snd_mpu401_uart_new (struct snd_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_opl3_create (struct snd_card*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_opl3**) ; 
 int snd_opl3_hwdep_new (struct snd_opl3*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int snd_es1688_probe(struct snd_card *card, unsigned int n)
{
	struct snd_es1688 *chip = card->private_data;
	struct snd_opl3 *opl3;
	int error;

	error = snd_es1688_pcm(card, chip, 0);
	if (error < 0)
		return error;

	error = snd_es1688_mixer(card, chip);
	if (error < 0)
		return error;

	strlcpy(card->driver, "ES1688", sizeof(card->driver));
	strlcpy(card->shortname, chip->pcm->name, sizeof(card->shortname));
	snprintf(card->longname, sizeof(card->longname),
		"%s at 0x%lx, irq %i, dma %i", chip->pcm->name, chip->port,
		 chip->irq, chip->dma8);

	if (fm_port[n] == SNDRV_AUTO_PORT)
		fm_port[n] = port[n];	/* share the same port */

	if (fm_port[n] > 0) {
		if (snd_opl3_create(card, fm_port[n], fm_port[n] + 2,
				OPL3_HW_OPL3, 0, &opl3) < 0)
			dev_warn(card->dev,
				 "opl3 not detected at 0x%lx\n", fm_port[n]);
		else {
			error =	snd_opl3_hwdep_new(opl3, 0, 1, NULL);
			if (error < 0)
				return error;
		}
	}

	if (mpu_irq[n] >= 0 && mpu_irq[n] != SNDRV_AUTO_IRQ &&
			chip->mpu_port > 0) {
		error = snd_mpu401_uart_new(card, 0, MPU401_HW_ES1688,
				chip->mpu_port, 0,
				mpu_irq[n], NULL);
		if (error < 0)
			return error;
	}

	return snd_card_register(card);
}