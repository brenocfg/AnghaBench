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
struct snd_mpu401 {scalar_t__ rmidi; int /*<<< orphan*/  timer_lock; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  _snd_mpu401_uart_interrupt (struct snd_mpu401*) ; 
 struct snd_mpu401* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct snd_mpu401* mpu ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void snd_mpu401_uart_timer(struct timer_list *t)
{
	struct snd_mpu401 *mpu = from_timer(mpu, t, timer);
	unsigned long flags;

	spin_lock_irqsave(&mpu->timer_lock, flags);
	/*mpu->mode |= MPU401_MODE_TIMER;*/
	mod_timer(&mpu->timer,  1 + jiffies);
	spin_unlock_irqrestore(&mpu->timer_lock, flags);
	if (mpu->rmidi)
		_snd_mpu401_uart_interrupt(mpu);
}