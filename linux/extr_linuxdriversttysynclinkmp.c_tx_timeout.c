#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  txtimeout; } ;
struct TYPE_7__ {scalar_t__ mode; } ;
struct TYPE_9__ {int tx_active; int /*<<< orphan*/  lock; scalar_t__ tx_get; scalar_t__ tx_put; scalar_t__ tx_count; TYPE_2__ icount; TYPE_1__ params; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_3__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 int /*<<< orphan*/  bh_transmit (TYPE_3__*) ; 
 scalar_t__ debug_level ; 
 TYPE_3__* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 TYPE_3__* info ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_timer ; 

__attribute__((used)) static void tx_timeout(struct timer_list *t)
{
	SLMP_INFO *info = from_timer(info, t, tx_timer);
	unsigned long flags;

	if ( debug_level >= DEBUG_LEVEL_INFO )
		printk( "%s(%d):%s tx_timeout()\n",
			__FILE__,__LINE__,info->device_name);
	if(info->tx_active && info->params.mode == MGSL_MODE_HDLC) {
		info->icount.txtimeout++;
	}
	spin_lock_irqsave(&info->lock,flags);
	info->tx_active = false;
	info->tx_count = info->tx_put = info->tx_get = 0;

	spin_unlock_irqrestore(&info->lock,flags);

#if SYNCLINK_GENERIC_HDLC
	if (info->netcount)
		hdlcdev_tx_done(info);
	else
#endif
		bh_transmit(info);
}