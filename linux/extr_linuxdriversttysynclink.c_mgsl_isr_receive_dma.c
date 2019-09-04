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
struct TYPE_2__ {int /*<<< orphan*/  buf_overrun; } ;
struct mgsl_struct {int rx_overflow; TYPE_1__ icount; int /*<<< orphan*/  pending_bh; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_RECEIVE ; 
 int BIT1 ; 
 int BIT3 ; 
 int BIT9 ; 
 int /*<<< orphan*/  CDIR ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 int /*<<< orphan*/  RDMR ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,int) ; 
 int usc_InDmaReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutDmaReg (struct mgsl_struct*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mgsl_isr_receive_dma( struct mgsl_struct *info )
{
	u16 status;
	
	/* clear interrupt pending and IUS bit for Rx DMA IRQ */
	usc_OutDmaReg( info, CDIR, BIT9 | BIT1 );

	/* Read the receive DMA status to identify interrupt type. */
	/* This also clears the status bits. */
	status = usc_InDmaReg( info, RDMR );

	if ( debug_level >= DEBUG_LEVEL_ISR )	
		printk("%s(%d):mgsl_isr_receive_dma(%s) status=%04X\n",
			__FILE__,__LINE__,info->device_name,status);
			
	info->pending_bh |= BH_RECEIVE;
	
	if ( status & BIT3 ) {
		info->rx_overflow = true;
		info->icount.buf_overrun++;
	}

}