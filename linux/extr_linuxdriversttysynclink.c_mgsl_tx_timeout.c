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
struct TYPE_4__ {scalar_t__ mode; int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  txtimeout; } ;
struct mgsl_struct {int tx_active; int /*<<< orphan*/  irq_spinlock; TYPE_2__ params; scalar_t__ xmit_tail; scalar_t__ xmit_head; scalar_t__ xmit_cnt; TYPE_1__ icount; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int HDLC_FLAG_HDLC_LOOPMODE ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 scalar_t__ MGSL_MODE_RAW ; 
 scalar_t__ debug_level ; 
 struct mgsl_struct* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct mgsl_struct* info ; 
 int /*<<< orphan*/  mgsl_bh_transmit (struct mgsl_struct*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_timer ; 
 int /*<<< orphan*/  usc_loopmode_cancel_transmit (struct mgsl_struct*) ; 

__attribute__((used)) static void mgsl_tx_timeout(struct timer_list *t)
{
	struct mgsl_struct *info = from_timer(info, t, tx_timer);
	unsigned long flags;
	
	if ( debug_level >= DEBUG_LEVEL_INFO )
		printk( "%s(%d):mgsl_tx_timeout(%s)\n",
			__FILE__,__LINE__,info->device_name);
	if(info->tx_active &&
	   (info->params.mode == MGSL_MODE_HDLC ||
	    info->params.mode == MGSL_MODE_RAW) ) {
		info->icount.txtimeout++;
	}
	spin_lock_irqsave(&info->irq_spinlock,flags);
	info->tx_active = false;
	info->xmit_cnt = info->xmit_head = info->xmit_tail = 0;

	if ( info->params.flags & HDLC_FLAG_HDLC_LOOPMODE )
		usc_loopmode_cancel_transmit( info );

	spin_unlock_irqrestore(&info->irq_spinlock,flags);
	
#if SYNCLINK_GENERIC_HDLC
	if (info->netcount)
		hdlcdev_tx_done(info);
	else
#endif
		mgsl_bh_transmit(info);
	
}