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
struct snd_mpu401 {int timer_invoked; int /*<<< orphan*/  timer_lock; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int MPU401_MODE_INPUT_TIMER ; 
 int MPU401_MODE_OUTPUT_TIMER ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_mpu401_uart_remove_timer (struct snd_mpu401 *mpu, int input)
{
	unsigned long flags;

	spin_lock_irqsave (&mpu->timer_lock, flags);
	if (mpu->timer_invoked) {
		mpu->timer_invoked &= input ? ~MPU401_MODE_INPUT_TIMER :
			~MPU401_MODE_OUTPUT_TIMER;
		if (! mpu->timer_invoked)
			del_timer(&mpu->timer);
	}
	spin_unlock_irqrestore (&mpu->timer_lock, flags);
}