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
struct snd_emu8k_pcm {int /*<<< orphan*/  timer_lock; scalar_t__ timer_running; int /*<<< orphan*/  timer; struct snd_emu8000* emu; } ;
struct snd_emu8000 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU8000_DCYSUSV_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void stop_voice(struct snd_emu8k_pcm *rec, int ch)
{
	unsigned long flags;
	struct snd_emu8000 *hw = rec->emu;

	EMU8000_DCYSUSV_WRITE(hw, ch, 0x807F);

	/* stop timer */
	spin_lock_irqsave(&rec->timer_lock, flags);
	if (rec->timer_running) {
		del_timer(&rec->timer);
		rec->timer_running = 0;
	}
	spin_unlock_irqrestore(&rec->timer_lock, flags);
}