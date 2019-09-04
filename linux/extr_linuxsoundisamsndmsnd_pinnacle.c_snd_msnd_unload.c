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
struct snd_msnd {int /*<<< orphan*/  irq; int /*<<< orphan*/  io; int /*<<< orphan*/  base; int /*<<< orphan*/  mappedbase; } ;
struct snd_card {struct snd_msnd* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFSIZE ; 
 int /*<<< orphan*/  DSP_NUMIO ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct snd_msnd*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 

__attribute__((used)) static void snd_msnd_unload(struct snd_card *card)
{
	struct snd_msnd *chip = card->private_data;

	iounmap(chip->mappedbase);
	release_mem_region(chip->base, BUFFSIZE);
	release_region(chip->io, DSP_NUMIO);
	free_irq(chip->irq, chip);
	snd_card_free(card);
}