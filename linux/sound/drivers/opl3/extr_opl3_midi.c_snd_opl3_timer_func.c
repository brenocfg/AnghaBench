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
struct timer_list {int dummy; } ;
struct snd_opl3_voice {scalar_t__ state; scalar_t__ note_off; int /*<<< orphan*/  chan; int /*<<< orphan*/  note; scalar_t__ note_off_check; } ;
struct snd_opl3 {int max_voices; int /*<<< orphan*/  sys_timer_lock; scalar_t__ sys_timer_status; int /*<<< orphan*/  tlist; int /*<<< orphan*/  voice_lock; struct snd_opl3_voice* voices; } ;

/* Variables and functions */
 struct snd_opl3* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct snd_opl3* opl3 ; 
 int /*<<< orphan*/  snd_opl3_note_off_unsafe (struct snd_opl3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tlist ; 

void snd_opl3_timer_func(struct timer_list *t)
{

	struct snd_opl3 *opl3 = from_timer(opl3, t, tlist);
	unsigned long flags;
	int again = 0;
	int i;

	spin_lock_irqsave(&opl3->voice_lock, flags);
	for (i = 0; i < opl3->max_voices; i++) {
		struct snd_opl3_voice *vp = &opl3->voices[i];
		if (vp->state > 0 && vp->note_off_check) {
			if (vp->note_off == jiffies)
				snd_opl3_note_off_unsafe(opl3, vp->note, 0,
							 vp->chan);
			else
				again++;
		}
	}
	spin_unlock_irqrestore(&opl3->voice_lock, flags);

	spin_lock_irqsave(&opl3->sys_timer_lock, flags);
	if (again)
		mod_timer(&opl3->tlist, jiffies + 1);	/* invoke again */
	else
		opl3->sys_timer_status = 0;
	spin_unlock_irqrestore(&opl3->sys_timer_lock, flags);
}