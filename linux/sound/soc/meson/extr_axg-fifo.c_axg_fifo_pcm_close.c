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
struct axg_fifo {int /*<<< orphan*/  irq; int /*<<< orphan*/  pclk; int /*<<< orphan*/  arb; } ;

/* Variables and functions */
 struct axg_fifo* axg_fifo_data (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axg_fifo_pcm_close(struct snd_pcm_substream *ss)
{
	struct axg_fifo *fifo = axg_fifo_data(ss);
	int ret;

	/* Put the memory arbitror back in reset */
	ret = reset_control_assert(fifo->arb);

	/* Disable fifo ip and register access */
	clk_disable_unprepare(fifo->pclk);

	/* remove IRQ */
	free_irq(fifo->irq, ss);

	return ret;
}