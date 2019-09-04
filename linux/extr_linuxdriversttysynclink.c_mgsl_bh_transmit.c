#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct TYPE_2__ {struct tty_struct* tty; } ;
struct mgsl_struct {int /*<<< orphan*/  irq_spinlock; scalar_t__ loopmode_send_done_requested; int /*<<< orphan*/  tx_active; int /*<<< orphan*/  device_name; TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_BH ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 
 int /*<<< orphan*/  usc_loopmode_send_done (struct mgsl_struct*) ; 

__attribute__((used)) static void mgsl_bh_transmit(struct mgsl_struct *info)
{
	struct tty_struct *tty = info->port.tty;
	unsigned long flags;
	
	if ( debug_level >= DEBUG_LEVEL_BH )
		printk( "%s(%d):mgsl_bh_transmit() entry on %s\n",
			__FILE__,__LINE__,info->device_name);

	if (tty)
		tty_wakeup(tty);

	/* if transmitter idle and loopmode_send_done_requested
	 * then start echoing RxD to TxD
	 */
	spin_lock_irqsave(&info->irq_spinlock,flags);
 	if ( !info->tx_active && info->loopmode_send_done_requested )
 		usc_loopmode_send_done( info );
	spin_unlock_irqrestore(&info->irq_spinlock,flags);
}