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
#define  PCM_LOCK_DEFAULT 130 
#define  PCM_LOCK_IRQ 129 
#define  PCM_LOCK_IRQSAVE 128 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  snd_pcm_link_rwlock ; 
 int /*<<< orphan*/  snd_pcm_link_rwsem ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __snd_pcm_stream_unlock_mode(struct snd_pcm_substream *substream,
					 unsigned int mode, unsigned long flags)
{
	if (substream->pcm->nonatomic) {
		mutex_unlock(&substream->self_group.mutex);
		up_read(&snd_pcm_link_rwsem);
	} else {
		spin_unlock(&substream->self_group.lock);

		switch (mode) {
		case PCM_LOCK_DEFAULT:
			read_unlock(&snd_pcm_link_rwlock);
			break;
		case PCM_LOCK_IRQ:
			read_unlock_irq(&snd_pcm_link_rwlock);
			break;
		case PCM_LOCK_IRQSAVE:
			read_unlock_irqrestore(&snd_pcm_link_rwlock, flags);
			break;
		}
	}
}