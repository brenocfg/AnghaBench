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
struct TYPE_2__ {int /*<<< orphan*/  rxover; int /*<<< orphan*/  rxidle; int /*<<< orphan*/  exithunt; int /*<<< orphan*/  rxabort; } ;
struct mgsl_struct {int loopmode_insert_requested; int cmr_value; TYPE_1__ icount; int /*<<< orphan*/  event_wait_q; } ;

/* Variables and functions */
 int BIT13 ; 
 int /*<<< orphan*/  CMR ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 int /*<<< orphan*/  RCSR ; 
 int /*<<< orphan*/  RECEIVE_STATUS ; 
 int /*<<< orphan*/  RICR ; 
 int RXSTATUS_ABORT_RECEIVED ; 
 int RXSTATUS_EXITED_HUNT ; 
 int RXSTATUS_IDLE_RECEIVED ; 
 int RXSTATUS_OVERRUN ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int) ; 
 int /*<<< orphan*/  usc_ClearIrqPendingBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usc_UnlatchRxstatusBits (struct mgsl_struct*,int) ; 
 scalar_t__ usc_loopmode_active (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_process_rxoverrun_sync (struct mgsl_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mgsl_isr_receive_status( struct mgsl_struct *info )
{
	u16 status = usc_InReg( info, RCSR );

	if ( debug_level >= DEBUG_LEVEL_ISR )
		printk("%s(%d):mgsl_isr_receive_status status=%04X\n",
			__FILE__,__LINE__,status);
			
 	if ( (status & RXSTATUS_ABORT_RECEIVED) && 
		info->loopmode_insert_requested &&
 		usc_loopmode_active(info) )
 	{
		++info->icount.rxabort;
	 	info->loopmode_insert_requested = false;
 
 		/* clear CMR:13 to start echoing RxD to TxD */
		info->cmr_value &= ~BIT13;
 		usc_OutReg(info, CMR, info->cmr_value);
 
		/* disable received abort irq (no longer required) */
	 	usc_OutReg(info, RICR,
 			(usc_InReg(info, RICR) & ~RXSTATUS_ABORT_RECEIVED));
 	}

	if (status & (RXSTATUS_EXITED_HUNT | RXSTATUS_IDLE_RECEIVED)) {
		if (status & RXSTATUS_EXITED_HUNT)
			info->icount.exithunt++;
		if (status & RXSTATUS_IDLE_RECEIVED)
			info->icount.rxidle++;
		wake_up_interruptible(&info->event_wait_q);
	}

	if (status & RXSTATUS_OVERRUN){
		info->icount.rxover++;
		usc_process_rxoverrun_sync( info );
	}

	usc_ClearIrqPendingBits( info, RECEIVE_STATUS );
	usc_UnlatchRxstatusBits( info, status );

}