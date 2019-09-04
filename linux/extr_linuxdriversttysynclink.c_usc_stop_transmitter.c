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
struct mgsl_struct {int tx_enabled; int tx_active; int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_ISR ; 
 int /*<<< orphan*/  DISABLE_UNCONDITIONAL ; 
 int /*<<< orphan*/  DmaCmd_ResetTxChannel ; 
 int /*<<< orphan*/  RTCmd_PurgeTxFifo ; 
 scalar_t__ TRANSMIT_DATA ; 
 scalar_t__ TRANSMIT_STATUS ; 
 int /*<<< orphan*/  TXSTATUS_ALL ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_ClearIrqPendingBits (struct mgsl_struct*,scalar_t__) ; 
 int /*<<< orphan*/  usc_DisableInterrupts (struct mgsl_struct*,scalar_t__) ; 
 int /*<<< orphan*/  usc_DmaCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_EnableTransmitter (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_RTCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_UnlatchTxstatusBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usc_stop_transmitter( struct mgsl_struct *info )
{
	if (debug_level >= DEBUG_LEVEL_ISR)
		printk("%s(%d):usc_stop_transmitter(%s)\n",
			 __FILE__,__LINE__, info->device_name );
			 
	del_timer(&info->tx_timer);	
			 
	usc_UnlatchTxstatusBits( info, TXSTATUS_ALL );
	usc_ClearIrqPendingBits( info, TRANSMIT_STATUS + TRANSMIT_DATA );
	usc_DisableInterrupts( info, TRANSMIT_STATUS + TRANSMIT_DATA );

	usc_EnableTransmitter(info,DISABLE_UNCONDITIONAL);
	usc_DmaCmd( info, DmaCmd_ResetTxChannel );
	usc_RTCmd( info, RTCmd_PurgeTxFifo );

	info->tx_enabled = false;
	info->tx_active = false;

}