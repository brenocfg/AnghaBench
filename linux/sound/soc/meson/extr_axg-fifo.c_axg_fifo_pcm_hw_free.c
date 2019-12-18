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
struct snd_pcm_substream {int dummy; } ;
struct axg_fifo {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL0_INT_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIFO_CTRL0 ; 
 int /*<<< orphan*/  FIFO_INT_COUNT_REPEAT ; 
 struct axg_fifo* axg_fifo_data (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 

__attribute__((used)) static int axg_fifo_pcm_hw_free(struct snd_pcm_substream *ss)
{
	struct axg_fifo *fifo = axg_fifo_data(ss);

	/* Disable the block count irq */
	regmap_update_bits(fifo->map, FIFO_CTRL0,
			   CTRL0_INT_EN(FIFO_INT_COUNT_REPEAT), 0);

	return snd_pcm_lib_free_pages(ss);
}