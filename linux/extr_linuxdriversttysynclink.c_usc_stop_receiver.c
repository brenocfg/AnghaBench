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
typedef  int /*<<< orphan*/  u16 ;
struct mgsl_struct {int rx_enabled; int rx_overflow; int rx_rcc_underrun; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int BIT13 ; 
 int /*<<< orphan*/  CCSR ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 int /*<<< orphan*/  DISABLE_UNCONDITIONAL ; 
 int /*<<< orphan*/  DmaCmd_ResetRxChannel ; 
 int RECEIVE_DATA ; 
 int RECEIVE_STATUS ; 
 int /*<<< orphan*/  RTCmd_PurgeRxFifo ; 
 int /*<<< orphan*/  RXSTATUS_ALL ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_ClearIrqPendingBits (struct mgsl_struct*,int) ; 
 int /*<<< orphan*/  usc_DisableInterrupts (struct mgsl_struct*,int) ; 
 int /*<<< orphan*/  usc_DmaCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_EnableReceiver (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_RTCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_UnlatchRxstatusBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usc_stop_receiver( struct mgsl_struct *info )
{
	if (debug_level >= DEBUG_LEVEL_ISR)
		printk("%s(%d):usc_stop_receiver(%s)\n",
			 __FILE__,__LINE__, info->device_name );
			 
	/* Disable receive DMA channel. */
	/* This also disables receive DMA channel interrupts */
	usc_DmaCmd( info, DmaCmd_ResetRxChannel );

	usc_UnlatchRxstatusBits( info, RXSTATUS_ALL );
	usc_ClearIrqPendingBits( info, RECEIVE_DATA | RECEIVE_STATUS );
	usc_DisableInterrupts( info, RECEIVE_DATA | RECEIVE_STATUS );

	usc_EnableReceiver(info,DISABLE_UNCONDITIONAL);

	/* This empties the receive FIFO and loads the RCC with RCLR */
	usc_OutReg( info, CCSR, (u16)(usc_InReg(info,CCSR) | BIT13) );
	usc_RTCmd( info, RTCmd_PurgeRxFifo );

	info->rx_enabled = false;
	info->rx_overflow = false;
	info->rx_rcc_underrun = false;
	
}