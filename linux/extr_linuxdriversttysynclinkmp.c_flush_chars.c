#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {scalar_t__ hw_stopped; scalar_t__ stopped; int /*<<< orphan*/  name; TYPE_2__* driver_data; } ;
struct TYPE_6__ {scalar_t__ mode; } ;
struct TYPE_7__ {scalar_t__ tx_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_buf; TYPE_1__ params; int /*<<< orphan*/  tx_active; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_2__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ sanity_check (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_load_dma_buffer (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tx_start (TYPE_2__*) ; 

__attribute__((used)) static void flush_chars(struct tty_struct *tty)
{
	SLMP_INFO *info = tty->driver_data;
	unsigned long flags;

	if ( debug_level >= DEBUG_LEVEL_INFO )
		printk( "%s(%d):%s flush_chars() entry tx_count=%d\n",
			__FILE__,__LINE__,info->device_name,info->tx_count);

	if (sanity_check(info, tty->name, "flush_chars"))
		return;

	if (info->tx_count <= 0 || tty->stopped || tty->hw_stopped ||
	    !info->tx_buf)
		return;

	if ( debug_level >= DEBUG_LEVEL_INFO )
		printk( "%s(%d):%s flush_chars() entry, starting transmitter\n",
			__FILE__,__LINE__,info->device_name );

	spin_lock_irqsave(&info->lock,flags);

	if (!info->tx_active) {
		if ( (info->params.mode == MGSL_MODE_HDLC) &&
			info->tx_count ) {
			/* operating in synchronous (frame oriented) mode */
			/* copy data from circular tx_buf to */
			/* transmit DMA buffer. */
			tx_load_dma_buffer(info,
				 info->tx_buf,info->tx_count);
		}
	 	tx_start(info);
	}

	spin_unlock_irqrestore(&info->lock,flags);
}