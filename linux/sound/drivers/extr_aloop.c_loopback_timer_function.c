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
struct timer_list {int dummy; } ;
struct loopback_pcm {TYPE_2__* cable; TYPE_1__* substream; scalar_t__ period_update_pending; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int stream; } ;

/* Variables and functions */
 struct loopback_pcm* dpcm ; 
 struct loopback_pcm* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int loopback_pos_update (TYPE_2__*) ; 
 int /*<<< orphan*/  loopback_timer_start (struct loopback_pcm*) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void loopback_timer_function(struct timer_list *t)
{
	struct loopback_pcm *dpcm = from_timer(dpcm, t, timer);
	unsigned long flags;

	spin_lock_irqsave(&dpcm->cable->lock, flags);
	if (loopback_pos_update(dpcm->cable) & (1 << dpcm->substream->stream)) {
		loopback_timer_start(dpcm);
		if (dpcm->period_update_pending) {
			dpcm->period_update_pending = 0;
			spin_unlock_irqrestore(&dpcm->cable->lock, flags);
			/* need to unlock before calling below */
			snd_pcm_period_elapsed(dpcm->substream);
			return;
		}
	}
	spin_unlock_irqrestore(&dpcm->cable->lock, flags);
}