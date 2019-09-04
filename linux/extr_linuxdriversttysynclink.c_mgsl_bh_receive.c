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
struct TYPE_2__ {scalar_t__ mode; } ;
struct mgsl_struct {int /*<<< orphan*/  irq_spinlock; scalar_t__ rx_rcc_underrun; int /*<<< orphan*/  device_name; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_BH ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 scalar_t__ debug_level ; 
 int mgsl_get_raw_rx_frame (struct mgsl_struct*) ; 
 int mgsl_get_rx_frame (struct mgsl_struct*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usc_start_receiver (struct mgsl_struct*) ; 

__attribute__((used)) static void mgsl_bh_receive(struct mgsl_struct *info)
{
	bool (*get_rx_frame)(struct mgsl_struct *info) =
		(info->params.mode == MGSL_MODE_HDLC ? mgsl_get_rx_frame : mgsl_get_raw_rx_frame);

	if ( debug_level >= DEBUG_LEVEL_BH )
		printk( "%s(%d):mgsl_bh_receive(%s)\n",
			__FILE__,__LINE__,info->device_name);
	
	do
	{
		if (info->rx_rcc_underrun) {
			unsigned long flags;
			spin_lock_irqsave(&info->irq_spinlock,flags);
			usc_start_receiver(info);
			spin_unlock_irqrestore(&info->irq_spinlock,flags);
			return;
		}
	} while(get_rx_frame(info));
}