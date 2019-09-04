#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ie0_value; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DCMD ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 scalar_t__ DIR ; 
 scalar_t__ DSR ; 
 scalar_t__ IE0 ; 
 int /*<<< orphan*/  SR1 ; 
 int SWABORT ; 
 int /*<<< orphan*/  TRC0 ; 
 scalar_t__ TXDMA ; 
 int TXRDYE ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,unsigned char) ; 
 unsigned char read_reg (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  write_reg16 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isr_txdmaok(SLMP_INFO * info)
{
	unsigned char status_reg1 = read_reg(info, SR1);

	write_reg(info, TXDMA + DIR, 0x00);	/* disable Tx DMA IRQs */
	write_reg(info, TXDMA + DSR, 0xc0); /* clear IRQs and disable DMA */
	write_reg(info, TXDMA + DCMD, SWABORT);	/* reset/init DMA channel */

	if ( debug_level >= DEBUG_LEVEL_ISR )
		printk("%s(%d):%s isr_txdmaok(), status=%02x\n",
			__FILE__,__LINE__,info->device_name,status_reg1);

	/* program TXRDY as FIFO empty flag, enable TXRDY IRQ */
	write_reg16(info, TRC0, 0);
	info->ie0_value |= TXRDYE;
	write_reg(info, IE0, info->ie0_value);
}