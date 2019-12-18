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
struct snd_m3 {int /*<<< orphan*/  reg_lock; } ;
struct m3_dma {unsigned int dma_size; unsigned int hwptr; int count; int period_size; int /*<<< orphan*/  running; struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 unsigned int snd_m3_get_pointer (struct snd_m3*,struct m3_dma*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_m3_update_ptr(struct snd_m3 *chip, struct m3_dma *s)
{
	struct snd_pcm_substream *subs = s->substream;
	unsigned int hwptr;
	int diff;

	if (! s->running)
		return;

	hwptr = snd_m3_get_pointer(chip, s, subs);

	/* try to avoid expensive modulo divisions */
	if (hwptr >= s->dma_size)
		hwptr %= s->dma_size;

	diff = s->dma_size + hwptr - s->hwptr;
	if (diff >= s->dma_size)
		diff %= s->dma_size;

	s->hwptr = hwptr;
	s->count += diff;

	if (s->count >= (signed)s->period_size) {

		if (s->count < 2 * (signed)s->period_size)
			s->count -= (signed)s->period_size;
		else
			s->count %= s->period_size;

		spin_unlock(&chip->reg_lock);
		snd_pcm_period_elapsed(subs);
		spin_lock(&chip->reg_lock);
	}
}