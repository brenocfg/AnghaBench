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
struct snd_pcm_substream {size_t number; size_t stream; struct loopback* private_data; } ;
struct loopback_cable {int /*<<< orphan*/  lock; int /*<<< orphan*/ ** streams; } ;
struct loopback {struct loopback_cable*** cables; } ;

/* Variables and functions */
 int get_cable_index (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  kfree (struct loopback_cable*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_cable(struct snd_pcm_substream *substream)
{
	struct loopback *loopback = substream->private_data;
	int dev = get_cable_index(substream);
	struct loopback_cable *cable;

	cable = loopback->cables[substream->number][dev];
	if (!cable)
		return;
	if (cable->streams[!substream->stream]) {
		/* other stream is still alive */
		spin_lock_irq(&cable->lock);
		cable->streams[substream->stream] = NULL;
		spin_unlock_irq(&cable->lock);
	} else {
		/* free the cable */
		loopback->cables[substream->number][dev] = NULL;
		kfree(cable);
	}
}