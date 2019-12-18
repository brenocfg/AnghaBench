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
struct dummy_systimer_pcm {int frac_pos; int /*<<< orphan*/  lock; } ;
typedef  int snd_pcm_uframes_t ;
struct TYPE_2__ {struct dummy_systimer_pcm* private_data; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  dummy_systimer_update (struct dummy_systimer_pcm*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static snd_pcm_uframes_t
dummy_systimer_pointer(struct snd_pcm_substream *substream)
{
	struct dummy_systimer_pcm *dpcm = substream->runtime->private_data;
	snd_pcm_uframes_t pos;

	spin_lock(&dpcm->lock);
	dummy_systimer_update(dpcm);
	pos = dpcm->frac_pos / HZ;
	spin_unlock(&dpcm->lock);
	return pos;
}