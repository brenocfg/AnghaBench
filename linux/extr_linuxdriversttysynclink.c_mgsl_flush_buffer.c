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
struct tty_struct {int /*<<< orphan*/  name; struct mgsl_struct* driver_data; } ;
struct mgsl_struct {int /*<<< orphan*/  irq_spinlock; int /*<<< orphan*/  tx_timer; scalar_t__ xmit_tail; scalar_t__ xmit_head; scalar_t__ xmit_cnt; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ mgsl_paranoia_check (struct mgsl_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

__attribute__((used)) static void mgsl_flush_buffer(struct tty_struct *tty)
{
	struct mgsl_struct *info = tty->driver_data;
	unsigned long flags;
	
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgsl_flush_buffer(%s) entry\n",
			 __FILE__,__LINE__, info->device_name );
	
	if (mgsl_paranoia_check(info, tty->name, "mgsl_flush_buffer"))
		return;
		
	spin_lock_irqsave(&info->irq_spinlock,flags); 
	info->xmit_cnt = info->xmit_head = info->xmit_tail = 0;
	del_timer(&info->tx_timer);	
	spin_unlock_irqrestore(&info->irq_spinlock,flags);
	
	tty_wakeup(tty);
}