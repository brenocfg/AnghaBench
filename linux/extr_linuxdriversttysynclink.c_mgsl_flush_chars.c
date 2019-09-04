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
struct tty_struct {scalar_t__ hw_stopped; scalar_t__ stopped; int /*<<< orphan*/  name; struct mgsl_struct* driver_data; } ;
struct TYPE_2__ {scalar_t__ mode; } ;
struct mgsl_struct {scalar_t__ xmit_cnt; int /*<<< orphan*/  irq_spinlock; int /*<<< orphan*/  xmit_buf; TYPE_1__ params; int /*<<< orphan*/  tx_active; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 scalar_t__ MGSL_MODE_RAW ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  mgsl_load_tx_dma_buffer (struct mgsl_struct*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mgsl_paranoia_check (struct mgsl_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usc_start_transmitter (struct mgsl_struct*) ; 

__attribute__((used)) static void mgsl_flush_chars(struct tty_struct *tty)
{
	struct mgsl_struct *info = tty->driver_data;
	unsigned long flags;
				
	if ( debug_level >= DEBUG_LEVEL_INFO )
		printk( "%s(%d):mgsl_flush_chars() entry on %s xmit_cnt=%d\n",
			__FILE__,__LINE__,info->device_name,info->xmit_cnt);
	
	if (mgsl_paranoia_check(info, tty->name, "mgsl_flush_chars"))
		return;

	if (info->xmit_cnt <= 0 || tty->stopped || tty->hw_stopped ||
	    !info->xmit_buf)
		return;

	if ( debug_level >= DEBUG_LEVEL_INFO )
		printk( "%s(%d):mgsl_flush_chars() entry on %s starting transmitter\n",
			__FILE__,__LINE__,info->device_name );

	spin_lock_irqsave(&info->irq_spinlock,flags);
	
	if (!info->tx_active) {
		if ( (info->params.mode == MGSL_MODE_HDLC ||
			info->params.mode == MGSL_MODE_RAW) && info->xmit_cnt ) {
			/* operating in synchronous (frame oriented) mode */
			/* copy data from circular xmit_buf to */
			/* transmit DMA buffer. */
			mgsl_load_tx_dma_buffer(info,
				 info->xmit_buf,info->xmit_cnt);
		}
	 	usc_start_transmitter(info);
	}
	
	spin_unlock_irqrestore(&info->irq_spinlock,flags);
	
}