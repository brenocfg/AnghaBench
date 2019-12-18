#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct snd_sgio2audio {int /*<<< orphan*/  ring_base_dma; int /*<<< orphan*/  ring_base; TYPE_1__* card; int /*<<< orphan*/ * channel; } ;
struct TYPE_8__ {int /*<<< orphan*/  control; } ;
struct TYPE_9__ {TYPE_2__ audio; } ;
struct TYPE_11__ {TYPE_3__ perif; } ;
struct TYPE_10__ {size_t idx; int /*<<< orphan*/  irq; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  AUDIO_CONTROL_RESET ; 
 int /*<<< orphan*/  MACEISA_RINGBUFFERS_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_sgio2audio*) ; 
 TYPE_5__* mace ; 
 TYPE_4__* snd_sgio2_isr_table ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_sgio2audio_free(struct snd_sgio2audio *chip)
{
	int i;

	/* reset interface */
	writeq(AUDIO_CONTROL_RESET, &mace->perif.audio.control);
	udelay(1);
	writeq(0, &mace->perif.audio.control);

	/* release IRQ's */
	for (i = 0; i < ARRAY_SIZE(snd_sgio2_isr_table); i++)
		free_irq(snd_sgio2_isr_table[i].irq,
			 &chip->channel[snd_sgio2_isr_table[i].idx]);

	dma_free_coherent(chip->card->dev, MACEISA_RINGBUFFERS_SIZE,
			  chip->ring_base, chip->ring_base_dma);

	/* release card data */
	kfree(chip);
	return 0;
}