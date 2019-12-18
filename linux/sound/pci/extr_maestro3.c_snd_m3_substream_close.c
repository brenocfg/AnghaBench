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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_m3 {int /*<<< orphan*/  reg_lock; } ;
struct m3_dma {scalar_t__ opened; scalar_t__ running; scalar_t__ in_lists; int /*<<< orphan*/ * index; int /*<<< orphan*/ * index_list; scalar_t__ substream; } ;
struct TYPE_2__ {struct m3_dma* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_m3_pcm_stop (struct snd_m3*,struct m3_dma*,scalar_t__) ; 
 int /*<<< orphan*/  snd_m3_remove_list (struct snd_m3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
snd_m3_substream_close(struct snd_m3 *chip, struct snd_pcm_substream *subs)
{
	struct m3_dma *s = subs->runtime->private_data;

	if (s == NULL)
		return; /* not opened properly */

	spin_lock_irq(&chip->reg_lock);
	if (s->substream && s->running)
		snd_m3_pcm_stop(chip, s, s->substream); /* does this happen? */
	if (s->in_lists) {
		snd_m3_remove_list(chip, s->index_list[0], s->index[0]);
		snd_m3_remove_list(chip, s->index_list[1], s->index[1]);
		snd_m3_remove_list(chip, s->index_list[2], s->index[2]);
		s->in_lists = 0;
	}
	s->running = 0;
	s->opened = 0;
	spin_unlock_irq(&chip->reg_lock);
}