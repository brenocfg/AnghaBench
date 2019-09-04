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
struct TYPE_4__ {TYPE_1__* tty; } ;
struct mgsl_struct {scalar_t__ xmit_cnt; int tx_active; int /*<<< orphan*/  pending_bh; TYPE_2__ port; } ;
struct TYPE_3__ {scalar_t__ hw_stopped; scalar_t__ stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_TRANSMIT ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 int /*<<< orphan*/  TRANSMIT_DATA ; 
 scalar_t__ WAKEUP_CHARS ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  usc_ClearIrqPendingBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_load_txfifo (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_stop_transmitter (struct mgsl_struct*) ; 

__attribute__((used)) static void mgsl_isr_transmit_data( struct mgsl_struct *info )
{
	if ( debug_level >= DEBUG_LEVEL_ISR )	
		printk("%s(%d):mgsl_isr_transmit_data xmit_cnt=%d\n",
			__FILE__,__LINE__,info->xmit_cnt);
			
	usc_ClearIrqPendingBits( info, TRANSMIT_DATA );
	
	if (info->port.tty->stopped || info->port.tty->hw_stopped) {
		usc_stop_transmitter(info);
		return;
	}
	
	if ( info->xmit_cnt )
		usc_load_txfifo( info );
	else
		info->tx_active = false;
		
	if (info->xmit_cnt < WAKEUP_CHARS)
		info->pending_bh |= BH_TRANSMIT;

}