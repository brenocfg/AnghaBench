#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ mode; } ;
struct TYPE_6__ {unsigned char ie1_value; int /*<<< orphan*/  lock; TYPE_1__ params; scalar_t__ tx_active; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_2__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ CMD ; 
 scalar_t__ DCMD ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ DSR ; 
 unsigned char IDLE ; 
 scalar_t__ IE1 ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 scalar_t__ SR1 ; 
 unsigned char SWABORT ; 
 unsigned char TXABORT ; 
 scalar_t__ TXDMA ; 
 unsigned char UDRN ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_reg (TYPE_2__*,scalar_t__,unsigned char) ; 

__attribute__((used)) static int tx_abort(SLMP_INFO * info)
{
 	unsigned long flags;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s tx_abort()\n",
			__FILE__,__LINE__,info->device_name);

	spin_lock_irqsave(&info->lock,flags);
	if ( info->tx_active && info->params.mode == MGSL_MODE_HDLC ) {
		info->ie1_value &= ~UDRN;
		info->ie1_value |= IDLE;
		write_reg(info, IE1, info->ie1_value);	/* disable tx status interrupts */
		write_reg(info, SR1, (unsigned char)(IDLE + UDRN));	/* clear pending */

		write_reg(info, TXDMA + DSR, 0);		/* disable DMA channel */
		write_reg(info, TXDMA + DCMD, SWABORT);	/* reset/init DMA channel */

   		write_reg(info, CMD, TXABORT);
	}
	spin_unlock_irqrestore(&info->lock,flags);
	return 0;
}