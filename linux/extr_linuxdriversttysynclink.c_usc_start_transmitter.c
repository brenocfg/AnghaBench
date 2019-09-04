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
struct TYPE_4__ {int flags; scalar_t__ mode; } ;
struct mgsl_struct {int drop_rts_on_tx_done; int serial_signals; int tx_active; size_t start_tx_dma_buffer; int num_tx_dma_buffers; int tx_enabled; TYPE_2__ params; int /*<<< orphan*/  tx_timer; TYPE_1__* tx_buffer_list; scalar_t__ xmit_cnt; int /*<<< orphan*/  device_name; } ;
struct TYPE_3__ {unsigned int rcc; int phys_entry; } ;

/* Variables and functions */
 int BIT0 ; 
 int BIT2 ; 
 int BIT3 ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 int /*<<< orphan*/  DICR ; 
 int /*<<< orphan*/  DmaCmd_InitTxChannel ; 
 int /*<<< orphan*/  DmaCmd_ResetTxChannel ; 
 int /*<<< orphan*/  ENABLE_AUTO_CTS ; 
 int /*<<< orphan*/  ENABLE_UNCONDITIONAL ; 
 int HDLC_FLAG_AUTO_CTS ; 
 int HDLC_FLAG_AUTO_RTS ; 
 scalar_t__ MGSL_MODE_ASYNC ; 
 scalar_t__ MGSL_MODE_RAW ; 
 int /*<<< orphan*/  NTARL ; 
 int /*<<< orphan*/  NTARU ; 
 int /*<<< orphan*/  RTCmd_PurgeTxFifo ; 
 int SerialSignal_RTS ; 
 int /*<<< orphan*/  TCLR ; 
 int /*<<< orphan*/  TCmd_SendFrame ; 
 int /*<<< orphan*/  TDIAR ; 
 scalar_t__ TRANSMIT_DATA ; 
 scalar_t__ TRANSMIT_STATUS ; 
 int /*<<< orphan*/  TXSTATUS_ALL ; 
 scalar_t__ debug_level ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_ClearIrqPendingBits (struct mgsl_struct*,scalar_t__) ; 
 int /*<<< orphan*/  usc_DmaCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_EnableInterrupts (struct mgsl_struct*,scalar_t__) ; 
 int /*<<< orphan*/  usc_EnableTransmitter (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int usc_InDmaReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutDmaReg (struct mgsl_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usc_RTCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_TCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_UnlatchTxstatusBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_get_serial_signals (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_load_txfifo (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_set_serial_signals (struct mgsl_struct*) ; 

__attribute__((used)) static void usc_start_transmitter( struct mgsl_struct *info )
{
	u32 phys_addr;
	unsigned int FrameSize;

	if (debug_level >= DEBUG_LEVEL_ISR)
		printk("%s(%d):usc_start_transmitter(%s)\n",
			 __FILE__,__LINE__, info->device_name );
			 
	if ( info->xmit_cnt ) {

		/* If auto RTS enabled and RTS is inactive, then assert */
		/* RTS and set a flag indicating that the driver should */
		/* negate RTS when the transmission completes. */

		info->drop_rts_on_tx_done = false;

		if ( info->params.flags & HDLC_FLAG_AUTO_RTS ) {
			usc_get_serial_signals( info );
			if ( !(info->serial_signals & SerialSignal_RTS) ) {
				info->serial_signals |= SerialSignal_RTS;
				usc_set_serial_signals( info );
				info->drop_rts_on_tx_done = true;
			}
		}


		if ( info->params.mode == MGSL_MODE_ASYNC ) {
			if ( !info->tx_active ) {
				usc_UnlatchTxstatusBits(info, TXSTATUS_ALL);
				usc_ClearIrqPendingBits(info, TRANSMIT_STATUS + TRANSMIT_DATA);
				usc_EnableInterrupts(info, TRANSMIT_DATA);
				usc_load_txfifo(info);
			}
		} else {
			/* Disable transmit DMA controller while programming. */
			usc_DmaCmd( info, DmaCmd_ResetTxChannel );
			
			/* Transmit DMA buffer is loaded, so program USC */
			/* to send the frame contained in the buffers.	 */

			FrameSize = info->tx_buffer_list[info->start_tx_dma_buffer].rcc;

			/* if operating in Raw sync mode, reset the rcc component
			 * of the tx dma buffer entry, otherwise, the serial controller
			 * will send a closing sync char after this count.
			 */
	    		if ( info->params.mode == MGSL_MODE_RAW )
				info->tx_buffer_list[info->start_tx_dma_buffer].rcc = 0;

			/* Program the Transmit Character Length Register (TCLR) */
			/* and clear FIFO (TCC is loaded with TCLR on FIFO clear) */
			usc_OutReg( info, TCLR, (u16)FrameSize );

			usc_RTCmd( info, RTCmd_PurgeTxFifo );

			/* Program the address of the 1st DMA Buffer Entry in linked list */
			phys_addr = info->tx_buffer_list[info->start_tx_dma_buffer].phys_entry;
			usc_OutDmaReg( info, NTARL, (u16)phys_addr );
			usc_OutDmaReg( info, NTARU, (u16)(phys_addr >> 16) );

			usc_UnlatchTxstatusBits( info, TXSTATUS_ALL );
			usc_ClearIrqPendingBits( info, TRANSMIT_STATUS );
			usc_EnableInterrupts( info, TRANSMIT_STATUS );

			if ( info->params.mode == MGSL_MODE_RAW &&
					info->num_tx_dma_buffers > 1 ) {
			   /* When running external sync mode, attempt to 'stream' transmit  */
			   /* by filling tx dma buffers as they become available. To do this */
			   /* we need to enable Tx DMA EOB Status interrupts :               */
			   /*                                                                */
			   /* 1. Arm End of Buffer (EOB) Transmit DMA Interrupt (BIT2 of TDIAR) */
			   /* 2. Enable Transmit DMA Interrupts (BIT0 of DICR) */

			   usc_OutDmaReg( info, TDIAR, BIT2|BIT3 );
			   usc_OutDmaReg( info, DICR, (u16)(usc_InDmaReg(info,DICR) | BIT0) );
			}

			/* Initialize Transmit DMA Channel */
			usc_DmaCmd( info, DmaCmd_InitTxChannel );
			
			usc_TCmd( info, TCmd_SendFrame );
			
			mod_timer(&info->tx_timer, jiffies +
					msecs_to_jiffies(5000));
		}
		info->tx_active = true;
	}

	if ( !info->tx_enabled ) {
		info->tx_enabled = true;
		if ( info->params.flags & HDLC_FLAG_AUTO_CTS )
			usc_EnableTransmitter(info,ENABLE_AUTO_CTS);
		else
			usc_EnableTransmitter(info,ENABLE_UNCONDITIONAL);
	}

}