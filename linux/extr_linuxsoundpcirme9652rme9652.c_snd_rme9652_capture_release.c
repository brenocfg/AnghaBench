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
struct snd_rme9652 {int capture_pid; int /*<<< orphan*/  lock; int /*<<< orphan*/ * capture_substream; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 struct snd_rme9652* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_rme9652_capture_release(struct snd_pcm_substream *substream)
{
	struct snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);

	spin_lock_irq(&rme9652->lock);

	rme9652->capture_pid = -1;
	rme9652->capture_substream = NULL;

	spin_unlock_irq(&rme9652->lock);
	return 0;
}