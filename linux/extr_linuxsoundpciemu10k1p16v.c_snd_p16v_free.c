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
struct TYPE_2__ {scalar_t__ area; } ;
struct snd_emu10k1 {TYPE_1__ p16v_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_1__*) ; 

int snd_p16v_free(struct snd_emu10k1 *chip)
{
	// release the data
	if (chip->p16v_buffer.area) {
		snd_dma_free_pages(&chip->p16v_buffer);
		/*
		dev_dbg(chip->card->dev, "period lables free: %p\n",
			   &chip->p16v_buffer);
		*/
	}
	return 0;
}