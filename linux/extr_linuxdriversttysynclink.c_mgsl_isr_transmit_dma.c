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
typedef  int u16 ;
struct mgsl_struct {int /*<<< orphan*/  pending_bh; int /*<<< orphan*/  tx_dma_buffers_used; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_TRANSMIT ; 
 int BIT0 ; 
 int BIT2 ; 
 int BIT8 ; 
 int /*<<< orphan*/  CDIR ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 int /*<<< orphan*/  TDMR ; 
 scalar_t__ debug_level ; 
 scalar_t__ load_next_tx_holding_buffer (struct mgsl_struct*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,int) ; 
 int usc_InDmaReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutDmaReg (struct mgsl_struct*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mgsl_isr_transmit_dma( struct mgsl_struct *info )
{
	u16 status;

	/* clear interrupt pending and IUS bit for Tx DMA IRQ */
	usc_OutDmaReg(info, CDIR, BIT8 | BIT0 );

	/* Read the transmit DMA status to identify interrupt type. */
	/* This also clears the status bits. */

	status = usc_InDmaReg( info, TDMR );

	if ( debug_level >= DEBUG_LEVEL_ISR )
		printk("%s(%d):mgsl_isr_transmit_dma(%s) status=%04X\n",
			__FILE__,__LINE__,info->device_name,status);

	if ( status & BIT2 ) {
		--info->tx_dma_buffers_used;

		/* if there are transmit frames queued,
		 *  try to load the next one
		 */
		if ( load_next_tx_holding_buffer(info) ) {
			/* if call returns non-zero value, we have
			 * at least one free tx holding buffer
			 */
			info->pending_bh |= BH_TRANSMIT;
		}
	}

}