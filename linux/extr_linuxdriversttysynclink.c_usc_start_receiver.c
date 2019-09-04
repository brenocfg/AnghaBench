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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {scalar_t__ mode; int flags; } ;
struct mgsl_struct {int rx_enabled; TYPE_2__ params; TYPE_1__* rx_buffer_list; int /*<<< orphan*/  device_name; } ;
struct TYPE_3__ {int phys_entry; } ;

/* Variables and functions */
 int BIT1 ; 
 int BIT13 ; 
 int BIT2 ; 
 int BIT3 ; 
 int /*<<< orphan*/  CCSR ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 int /*<<< orphan*/  DICR ; 
 int /*<<< orphan*/  DmaCmd_InitRxChannel ; 
 int /*<<< orphan*/  ENABLE_AUTO_DCD ; 
 int /*<<< orphan*/  ENABLE_UNCONDITIONAL ; 
 int HDLC_FLAG_AUTO_DCD ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 scalar_t__ MGSL_MODE_RAW ; 
 int /*<<< orphan*/  NRARL ; 
 int /*<<< orphan*/  NRARU ; 
 int /*<<< orphan*/  RCmd_EnterHuntmode ; 
 int /*<<< orphan*/  RDIAR ; 
 int RECEIVE_DATA ; 
 int RECEIVE_STATUS ; 
 int /*<<< orphan*/  RTCmd_PurgeRxFifo ; 
 int /*<<< orphan*/  RXSTATUS_ALL ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  mgsl_reset_rx_dma_buffers (struct mgsl_struct*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_ClearIrqPendingBits (struct mgsl_struct*,int) ; 
 int /*<<< orphan*/  usc_DmaCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_EnableInterrupts (struct mgsl_struct*,int) ; 
 int /*<<< orphan*/  usc_EnableReceiver (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int usc_InDmaReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutDmaReg (struct mgsl_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usc_RCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_RTCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_UnlatchRxstatusBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_stop_receiver (struct mgsl_struct*) ; 

__attribute__((used)) static void usc_start_receiver( struct mgsl_struct *info )
{
	u32 phys_addr;
	
	if (debug_level >= DEBUG_LEVEL_ISR)
		printk("%s(%d):usc_start_receiver(%s)\n",
			 __FILE__,__LINE__, info->device_name );

	mgsl_reset_rx_dma_buffers( info );
	usc_stop_receiver( info );

	usc_OutReg( info, CCSR, (u16)(usc_InReg(info,CCSR) | BIT13) );
	usc_RTCmd( info, RTCmd_PurgeRxFifo );

	if ( info->params.mode == MGSL_MODE_HDLC ||
		info->params.mode == MGSL_MODE_RAW ) {
		/* DMA mode Transfers */
		/* Program the DMA controller. */
		/* Enable the DMA controller end of buffer interrupt. */

		/* program 16C32 with physical address of 1st DMA buffer entry */
		phys_addr = info->rx_buffer_list[0].phys_entry;
		usc_OutDmaReg( info, NRARL, (u16)phys_addr );
		usc_OutDmaReg( info, NRARU, (u16)(phys_addr >> 16) );

		usc_UnlatchRxstatusBits( info, RXSTATUS_ALL );
		usc_ClearIrqPendingBits( info, RECEIVE_DATA | RECEIVE_STATUS );
		usc_EnableInterrupts( info, RECEIVE_STATUS );

		/* 1. Arm End of Buffer (EOB) Receive DMA Interrupt (BIT2 of RDIAR) */
		/* 2. Enable Receive DMA Interrupts (BIT1 of DICR) */

		usc_OutDmaReg( info, RDIAR, BIT3 | BIT2 );
		usc_OutDmaReg( info, DICR, (u16)(usc_InDmaReg(info,DICR) | BIT1) );
		usc_DmaCmd( info, DmaCmd_InitRxChannel );
		if ( info->params.flags & HDLC_FLAG_AUTO_DCD )
			usc_EnableReceiver(info,ENABLE_AUTO_DCD);
		else
			usc_EnableReceiver(info,ENABLE_UNCONDITIONAL);
	} else {
		usc_UnlatchRxstatusBits(info, RXSTATUS_ALL);
		usc_ClearIrqPendingBits(info, RECEIVE_DATA | RECEIVE_STATUS);
		usc_EnableInterrupts(info, RECEIVE_DATA);

		usc_RTCmd( info, RTCmd_PurgeRxFifo );
		usc_RCmd( info, RCmd_EnterHuntmode );

		usc_EnableReceiver(info,ENABLE_UNCONDITIONAL);
	}

	usc_OutReg( info, CCSR, 0x1020 );

	info->rx_enabled = true;

}