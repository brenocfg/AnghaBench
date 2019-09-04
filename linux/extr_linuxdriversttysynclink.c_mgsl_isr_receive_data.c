#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  tty; } ;
struct mgsl_icount {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; int /*<<< orphan*/  rx; } ;
struct mgsl_struct {int ignore_status_mask; int read_status_mask; TYPE_1__ port; scalar_t__ io_base; struct mgsl_icount icount; } ;

/* Variables and functions */
 int ASYNC_SAK ; 
 int BIT3 ; 
 scalar_t__ CCAR ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 int LSBONLY ; 
 scalar_t__ RCSR ; 
 int /*<<< orphan*/  RCmd_SelectRicrRxFifostatus ; 
 int RDR ; 
 int /*<<< orphan*/  RECEIVE_DATA ; 
 scalar_t__ RICR ; 
 int /*<<< orphan*/  RTCmd_PurgeRxFifo ; 
 int /*<<< orphan*/  RXSTATUS_ALL ; 
 int RXSTATUS_BREAK_RECEIVED ; 
 int RXSTATUS_FRAMING_ERROR ; 
 int RXSTATUS_OVERRUN ; 
 int RXSTATUS_PARITY_ERROR ; 
 int TTY_BREAK ; 
 int TTY_FRAME ; 
 int TTY_OVERRUN ; 
 int TTY_PARITY ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  do_SAK (int /*<<< orphan*/ ) ; 
 unsigned char inb (scalar_t__) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (TYPE_1__*) ; 
 int tty_insert_flip_char (TYPE_1__*,unsigned char,int) ; 
 int /*<<< orphan*/  usc_ClearIrqPendingBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int usc_InReg (struct mgsl_struct*,scalar_t__) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,scalar_t__,int) ; 
 int /*<<< orphan*/  usc_RCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_RTCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_UnlatchRxstatusBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mgsl_isr_receive_data( struct mgsl_struct *info )
{
	int Fifocount;
	u16 status;
	int work = 0;
	unsigned char DataByte;
 	struct	mgsl_icount *icount = &info->icount;
	
	if ( debug_level >= DEBUG_LEVEL_ISR )	
		printk("%s(%d):mgsl_isr_receive_data\n",
			__FILE__,__LINE__);

	usc_ClearIrqPendingBits( info, RECEIVE_DATA );
	
	/* select FIFO status for RICR readback */
	usc_RCmd( info, RCmd_SelectRicrRxFifostatus );

	/* clear the Wordstatus bit so that status readback */
	/* only reflects the status of this byte */
	usc_OutReg( info, RICR+LSBONLY, (u16)(usc_InReg(info, RICR+LSBONLY) & ~BIT3 ));

	/* flush the receive FIFO */

	while( (Fifocount = (usc_InReg(info,RICR) >> 8)) ) {
		int flag;

		/* read one byte from RxFIFO */
		outw( (inw(info->io_base + CCAR) & 0x0780) | (RDR+LSBONLY),
		      info->io_base + CCAR );
		DataByte = inb( info->io_base + CCAR );

		/* get the status of the received byte */
		status = usc_InReg(info, RCSR);
		if ( status & (RXSTATUS_FRAMING_ERROR | RXSTATUS_PARITY_ERROR |
				RXSTATUS_OVERRUN | RXSTATUS_BREAK_RECEIVED) )
			usc_UnlatchRxstatusBits(info,RXSTATUS_ALL);
		
		icount->rx++;
		
		flag = 0;
		if ( status & (RXSTATUS_FRAMING_ERROR | RXSTATUS_PARITY_ERROR |
				RXSTATUS_OVERRUN | RXSTATUS_BREAK_RECEIVED) ) {
			printk("rxerr=%04X\n",status);
			/* update error statistics */
			if ( status & RXSTATUS_BREAK_RECEIVED ) {
				status &= ~(RXSTATUS_FRAMING_ERROR | RXSTATUS_PARITY_ERROR);
				icount->brk++;
			} else if (status & RXSTATUS_PARITY_ERROR)
				icount->parity++;
			else if (status & RXSTATUS_FRAMING_ERROR)
				icount->frame++;
			else if (status & RXSTATUS_OVERRUN) {
				/* must issue purge fifo cmd before */
				/* 16C32 accepts more receive chars */
				usc_RTCmd(info,RTCmd_PurgeRxFifo);
				icount->overrun++;
			}

			/* discard char if tty control flags say so */
			if (status & info->ignore_status_mask)
				continue;
				
			status &= info->read_status_mask;
		
			if (status & RXSTATUS_BREAK_RECEIVED) {
				flag = TTY_BREAK;
				if (info->port.flags & ASYNC_SAK)
					do_SAK(info->port.tty);
			} else if (status & RXSTATUS_PARITY_ERROR)
				flag = TTY_PARITY;
			else if (status & RXSTATUS_FRAMING_ERROR)
				flag = TTY_FRAME;
		}	/* end of if (error) */
		tty_insert_flip_char(&info->port, DataByte, flag);
		if (status & RXSTATUS_OVERRUN) {
			/* Overrun is special, since it's
			 * reported immediately, and doesn't
			 * affect the current character
			 */
			work += tty_insert_flip_char(&info->port, 0, TTY_OVERRUN);
		}
	}

	if ( debug_level >= DEBUG_LEVEL_ISR ) {
		printk("%s(%d):rx=%d brk=%d parity=%d frame=%d overrun=%d\n",
			__FILE__,__LINE__,icount->rx,icount->brk,
			icount->parity,icount->frame,icount->overrun);
	}
			
	if(work)
		tty_flip_buffer_push(&info->port);
}