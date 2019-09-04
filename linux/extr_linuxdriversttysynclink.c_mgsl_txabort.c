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
struct TYPE_2__ {scalar_t__ mode; int flags; } ;
struct mgsl_struct {int /*<<< orphan*/  irq_spinlock; TYPE_1__ params; scalar_t__ tx_active; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int HDLC_FLAG_HDLC_LOOPMODE ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 int /*<<< orphan*/  TCmd_SendAbort ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usc_TCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_loopmode_cancel_transmit (struct mgsl_struct*) ; 

__attribute__((used)) static int mgsl_txabort(struct mgsl_struct * info)
{
 	unsigned long flags;
 
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgsl_txabort(%s)\n", __FILE__,__LINE__,
			info->device_name);
			
	spin_lock_irqsave(&info->irq_spinlock,flags);
	if ( info->tx_active && info->params.mode == MGSL_MODE_HDLC )
	{
		if ( info->params.flags & HDLC_FLAG_HDLC_LOOPMODE )
			usc_loopmode_cancel_transmit( info );
		else
			usc_TCmd(info,TCmd_SendAbort);
	}
	spin_unlock_irqrestore(&info->irq_spinlock,flags);
	return 0;
	
}