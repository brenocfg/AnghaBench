#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ mode; } ;
struct TYPE_12__ {int ie0_value; int rx_buf_count; int rx_overflow; int rx_enabled; TYPE_3__* rx_buf_list_ex; scalar_t__ current_rx_buf; TYPE_2__* rx_buf_list; TYPE_1__ params; int /*<<< orphan*/  device_name; } ;
struct TYPE_11__ {int /*<<< orphan*/  phys_entry; } ;
struct TYPE_10__ {int status; } ;
typedef  TYPE_4__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ BFL ; 
 scalar_t__ CDA ; 
 scalar_t__ CMD ; 
 scalar_t__ DCMD ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 scalar_t__ DIR ; 
 scalar_t__ DSR ; 
 scalar_t__ EDA ; 
 scalar_t__ IE0 ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 scalar_t__ RXDMA ; 
 int RXENABLE ; 
 int RXRDYE ; 
 int RXRESET ; 
 int /*<<< orphan*/  SCABUFSIZE ; 
 int SWABORT ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_status_reg (TYPE_4__*) ; 
 int /*<<< orphan*/  write_reg (TYPE_4__*,scalar_t__,int) ; 
 int /*<<< orphan*/  write_reg16 (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx_start(SLMP_INFO *info)
{
	int i;

	if (debug_level >= DEBUG_LEVEL_ISR)
		printk("%s(%d):%s rx_start()\n",
			 __FILE__,__LINE__, info->device_name );

	write_reg(info, CMD, RXRESET);

	if ( info->params.mode == MGSL_MODE_HDLC ) {
		/* HDLC, disabe IRQ on rxdata */
		info->ie0_value &= ~RXRDYE;
		write_reg(info, IE0, info->ie0_value);

		/* Reset all Rx DMA buffers and program rx dma */
		write_reg(info, RXDMA + DSR, 0);		/* disable Rx DMA */
		write_reg(info, RXDMA + DCMD, SWABORT);	/* reset/init Rx DMA */

		for (i = 0; i < info->rx_buf_count; i++) {
			info->rx_buf_list[i].status = 0xff;

			// throttle to 4 shared memory writes at a time to prevent
			// hogging local bus (keep latency time for DMA requests low).
			if (!(i % 4))
				read_status_reg(info);
		}
		info->current_rx_buf = 0;

		/* set current/1st descriptor address */
		write_reg16(info, RXDMA + CDA,
			info->rx_buf_list_ex[0].phys_entry);

		/* set new last rx descriptor address */
		write_reg16(info, RXDMA + EDA,
			info->rx_buf_list_ex[info->rx_buf_count - 1].phys_entry);

		/* set buffer length (shared by all rx dma data buffers) */
		write_reg16(info, RXDMA + BFL, SCABUFSIZE);

		write_reg(info, RXDMA + DIR, 0x60);	/* enable Rx DMA interrupts (EOM/BOF) */
		write_reg(info, RXDMA + DSR, 0xf2);	/* clear Rx DMA IRQs, enable Rx DMA */
	} else {
		/* async, enable IRQ on rxdata */
		info->ie0_value |= RXRDYE;
		write_reg(info, IE0, info->ie0_value);
	}

	write_reg(info, CMD, RXENABLE);

	info->rx_overflow = false;
	info->rx_enabled = true;
}