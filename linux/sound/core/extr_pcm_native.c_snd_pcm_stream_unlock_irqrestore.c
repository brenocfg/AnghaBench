#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  mutex; } ;
struct snd_pcm_substream {TYPE_2__ self_group; TYPE_1__* pcm; } ;
struct TYPE_3__ {scalar_t__ nonatomic; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_pcm_stream_unlock_irqrestore(struct snd_pcm_substream *substream,
				      unsigned long flags)
{
	if (substream->pcm->nonatomic)
		mutex_unlock(&substream->self_group.mutex);
	else
		spin_unlock_irqrestore(&substream->self_group.lock, flags);
}