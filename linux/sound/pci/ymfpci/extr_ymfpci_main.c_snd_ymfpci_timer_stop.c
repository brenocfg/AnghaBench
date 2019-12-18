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
struct snd_ymfpci {int /*<<< orphan*/  reg_lock; } ;
struct snd_timer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  YDSXGR_TIMERCTRL ; 
 struct snd_ymfpci* snd_timer_chip (struct snd_timer*) ; 
 int /*<<< orphan*/  snd_ymfpci_writeb (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_ymfpci_timer_stop(struct snd_timer *timer)
{
	struct snd_ymfpci *chip;
	unsigned long flags;

	chip = snd_timer_chip(timer);
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_ymfpci_writeb(chip, YDSXGR_TIMERCTRL, 0x00);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	return 0;
}