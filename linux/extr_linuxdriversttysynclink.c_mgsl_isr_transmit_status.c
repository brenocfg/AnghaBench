#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_6__ {TYPE_2__* tty; } ;
struct TYPE_4__ {int /*<<< orphan*/  txunder; int /*<<< orphan*/  txabort; int /*<<< orphan*/  txok; } ;
struct mgsl_struct {int tx_active; int drop_rts_on_tx_done; int serial_signals; int /*<<< orphan*/  pending_bh; TYPE_3__ port; int /*<<< orphan*/  tx_timer; scalar_t__ xmit_tail; scalar_t__ xmit_head; scalar_t__ xmit_cnt; TYPE_1__ icount; } ;
struct TYPE_5__ {scalar_t__ hw_stopped; scalar_t__ stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_TRANSMIT ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 int /*<<< orphan*/  DmaCmd_ResetTxChannel ; 
 int /*<<< orphan*/  RTCmd_PurgeTxFifo ; 
 int SerialSignal_RTS ; 
 int /*<<< orphan*/  TCSR ; 
 int /*<<< orphan*/  TRANSMIT_STATUS ; 
 int TXSTATUS_ABORT_SENT ; 
 int TXSTATUS_EOF_SENT ; 
 int TXSTATUS_UNDERRUN ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int) ; 
 int /*<<< orphan*/  usc_ClearIrqPendingBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_DmaCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_RTCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_UnlatchTxstatusBits (struct mgsl_struct*,int) ; 
 int /*<<< orphan*/  usc_get_serial_signals (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_set_serial_signals (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_stop_transmitter (struct mgsl_struct*) ; 

__attribute__((used)) static void mgsl_isr_transmit_status( struct mgsl_struct *info )
{
	u16 status = usc_InReg( info, TCSR );

	if ( debug_level >= DEBUG_LEVEL_ISR )	
		printk("%s(%d):mgsl_isr_transmit_status status=%04X\n",
			__FILE__,__LINE__,status);
	
	usc_ClearIrqPendingBits( info, TRANSMIT_STATUS );
	usc_UnlatchTxstatusBits( info, status );
	
	if ( status & (TXSTATUS_UNDERRUN | TXSTATUS_ABORT_SENT) )
	{
		/* finished sending HDLC abort. This may leave	*/
		/* the TxFifo with data from the aborted frame	*/
		/* so purge the TxFifo. Also shutdown the DMA	*/
		/* channel in case there is data remaining in 	*/
		/* the DMA buffer				*/
 		usc_DmaCmd( info, DmaCmd_ResetTxChannel );
 		usc_RTCmd( info, RTCmd_PurgeTxFifo );
	}
 
	if ( status & TXSTATUS_EOF_SENT )
		info->icount.txok++;
	else if ( status & TXSTATUS_UNDERRUN )
		info->icount.txunder++;
	else if ( status & TXSTATUS_ABORT_SENT )
		info->icount.txabort++;
	else
		info->icount.txunder++;
			
	info->tx_active = false;
	info->xmit_cnt = info->xmit_head = info->xmit_tail = 0;
	del_timer(&info->tx_timer);	
	
	if ( info->drop_rts_on_tx_done ) {
		usc_get_serial_signals( info );
		if ( info->serial_signals & SerialSignal_RTS ) {
			info->serial_signals &= ~SerialSignal_RTS;
			usc_set_serial_signals( info );
		}
		info->drop_rts_on_tx_done = false;
	}

#if SYNCLINK_GENERIC_HDLC
	if (info->netcount)
		hdlcdev_tx_done(info);
	else 
#endif
	{
		if (info->port.tty->stopped || info->port.tty->hw_stopped) {
			usc_stop_transmitter(info);
			return;
		}
		info->pending_bh |= BH_TRANSMIT;
	}

}