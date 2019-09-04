#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char ie1_value; unsigned char ie0_value; int tx_enabled; int tx_active; int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ CMD ; 
 scalar_t__ DCMD ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 scalar_t__ DSR ; 
 unsigned char IDLE ; 
 scalar_t__ IE0 ; 
 scalar_t__ IE1 ; 
 scalar_t__ SR1 ; 
 unsigned char SWABORT ; 
 scalar_t__ TXDMA ; 
 unsigned char TXRDYE ; 
 unsigned char TXRESET ; 
 unsigned char UDRN ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg (TYPE_1__*,scalar_t__,unsigned char) ; 

__attribute__((used)) static void tx_stop( SLMP_INFO *info )
{
	if (debug_level >= DEBUG_LEVEL_ISR)
		printk("%s(%d):%s tx_stop()\n",
			 __FILE__,__LINE__, info->device_name );

	del_timer(&info->tx_timer);

	write_reg(info, TXDMA + DSR, 0);		/* disable DMA channel */
	write_reg(info, TXDMA + DCMD, SWABORT);	/* reset/init DMA channel */

	write_reg(info, CMD, TXRESET);

	info->ie1_value &= ~(UDRN + IDLE);
	write_reg(info, IE1, info->ie1_value);	/* disable tx status interrupts */
	write_reg(info, SR1, (unsigned char)(IDLE + UDRN));	/* clear pending */

	info->ie0_value &= ~TXRDYE;
	write_reg(info, IE0, info->ie0_value);	/* disable tx data interrupts */

	info->tx_enabled = false;
	info->tx_active = false;
}