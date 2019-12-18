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
struct snd_korg1212 {size_t cardState; scalar_t__ stop_pending_cnt; int /*<<< orphan*/  lock; scalar_t__ currentBuffer; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  K1212_DEBUG_PRINTK (char*,int /*<<< orphan*/ ) ; 
 int snd_korg1212_SetupForPlay (struct snd_korg1212*) ; 
 struct snd_korg1212* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stateName ; 

__attribute__((used)) static int snd_korg1212_prepare(struct snd_pcm_substream *substream)
{
        struct snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);
	int rc;

	K1212_DEBUG_PRINTK("K1212_DEBUG: snd_korg1212_prepare [%s]\n",
			   stateName[korg1212->cardState]);

	spin_lock_irq(&korg1212->lock);

	/* FIXME: we should wait for ack! */
	if (korg1212->stop_pending_cnt > 0) {
		K1212_DEBUG_PRINTK("K1212_DEBUG: snd_korg1212_prepare - Stop is pending... [%s]\n",
				   stateName[korg1212->cardState]);
        	spin_unlock_irq(&korg1212->lock);
		return -EAGAIN;
		/*
		korg1212->sharedBufferPtr->cardCommand = 0;
		del_timer(&korg1212->timer);
		korg1212->stop_pending_cnt = 0;
		*/
	}

        rc = snd_korg1212_SetupForPlay(korg1212);

        korg1212->currentBuffer = 0;

        spin_unlock_irq(&korg1212->lock);

	return rc ? -EINVAL : 0;
}