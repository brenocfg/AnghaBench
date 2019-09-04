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
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ mode; } ;
struct mgsl_struct {int rx_rcc_underrun; int /*<<< orphan*/  pending_bh; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_RECEIVE ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 int /*<<< orphan*/  DISABLE_UNCONDITIONAL ; 
 int /*<<< orphan*/  DmaCmd_ResetRxChannel ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 int MISC ; 
 int MISCSTATUS_RCC_UNDERRUN ; 
 int /*<<< orphan*/  MISR ; 
 int RECEIVE_DATA ; 
 int RECEIVE_STATUS ; 
 int /*<<< orphan*/  RXSTATUS_ALL ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int) ; 
 int /*<<< orphan*/  usc_ClearIrqPendingBits (struct mgsl_struct*,int) ; 
 int /*<<< orphan*/  usc_DisableInterrupts (struct mgsl_struct*,int) ; 
 int /*<<< orphan*/  usc_DmaCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_EnableReceiver (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_UnlatchMiscstatusBits (struct mgsl_struct*,int) ; 
 int /*<<< orphan*/  usc_UnlatchRxstatusBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mgsl_isr_misc( struct mgsl_struct *info )
{
	u16 status = usc_InReg( info, MISR );

	if ( debug_level >= DEBUG_LEVEL_ISR )	
		printk("%s(%d):mgsl_isr_misc status=%04X\n",
			__FILE__,__LINE__,status);
			
	if ((status & MISCSTATUS_RCC_UNDERRUN) &&
	    (info->params.mode == MGSL_MODE_HDLC)) {

		/* turn off receiver and rx DMA */
		usc_EnableReceiver(info,DISABLE_UNCONDITIONAL);
		usc_DmaCmd(info, DmaCmd_ResetRxChannel);
		usc_UnlatchRxstatusBits(info, RXSTATUS_ALL);
		usc_ClearIrqPendingBits(info, RECEIVE_DATA | RECEIVE_STATUS);
		usc_DisableInterrupts(info, RECEIVE_DATA | RECEIVE_STATUS);

		/* schedule BH handler to restart receiver */
		info->pending_bh |= BH_RECEIVE;
		info->rx_rcc_underrun = true;
	}

	usc_ClearIrqPendingBits( info, MISC );
	usc_UnlatchMiscstatusBits( info, status );

}