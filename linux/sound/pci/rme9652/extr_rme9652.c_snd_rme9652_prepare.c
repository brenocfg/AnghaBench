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
struct snd_rme9652 {int /*<<< orphan*/  lock; int /*<<< orphan*/  running; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rme9652_reset_hw_pointer (struct snd_rme9652*) ; 
 struct snd_rme9652* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_rme9652_prepare(struct snd_pcm_substream *substream)
{
	struct snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	unsigned long flags;

	spin_lock_irqsave(&rme9652->lock, flags);
	if (!rme9652->running)
		rme9652_reset_hw_pointer(rme9652);
	spin_unlock_irqrestore(&rme9652->lock, flags);
	return 0;
}