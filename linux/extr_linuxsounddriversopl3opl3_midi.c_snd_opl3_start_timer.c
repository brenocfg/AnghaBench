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
struct snd_opl3 {int sys_timer_status; int /*<<< orphan*/  sys_timer_lock; int /*<<< orphan*/  tlist; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_opl3_start_timer(struct snd_opl3 *opl3)
{
	unsigned long flags;
	spin_lock_irqsave(&opl3->sys_timer_lock, flags);
	if (! opl3->sys_timer_status) {
		mod_timer(&opl3->tlist, jiffies + 1);
		opl3->sys_timer_status = 1;
	}
	spin_unlock_irqrestore(&opl3->sys_timer_lock, flags);
}