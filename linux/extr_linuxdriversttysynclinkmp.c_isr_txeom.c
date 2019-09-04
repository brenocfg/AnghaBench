#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_3__* tty; } ;
struct TYPE_12__ {scalar_t__ mode; } ;
struct TYPE_11__ {int /*<<< orphan*/  txok; int /*<<< orphan*/  txunder; } ;
struct TYPE_15__ {int ie0_value; unsigned char ie1_value; int tx_active; int drop_rts_on_tx_done; int /*<<< orphan*/  pending_bh; TYPE_4__ port; int /*<<< orphan*/  serial_signals; TYPE_2__ params; int /*<<< orphan*/  tx_timer; scalar_t__ tx_get; scalar_t__ tx_put; scalar_t__ tx_count; TYPE_1__ icount; int /*<<< orphan*/  device_name; } ;
struct TYPE_13__ {scalar_t__ hw_stopped; scalar_t__ stopped; } ;
typedef  TYPE_5__ SLMP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BH_TRANSMIT ; 
 scalar_t__ CMD ; 
 scalar_t__ DCMD ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 scalar_t__ DIR ; 
 scalar_t__ DSR ; 
 unsigned char IDLE ; 
 int /*<<< orphan*/  IE0 ; 
 scalar_t__ MGSL_MODE_ASYNC ; 
 scalar_t__ SR1 ; 
 unsigned char SWABORT ; 
 int /*<<< orphan*/  SerialSignal_RTS ; 
 unsigned char TXBUFCLR ; 
 scalar_t__ TXDMA ; 
 unsigned char TXENABLE ; 
 int TXRDYE ; 
 unsigned char TXRESET ; 
 unsigned char UDRN ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  set_signals (TYPE_5__*) ; 
 int /*<<< orphan*/  tx_stop (TYPE_5__*) ; 
 int /*<<< orphan*/  write_reg (TYPE_5__*,scalar_t__,unsigned char) ; 
 int /*<<< orphan*/  write_reg16 (TYPE_5__*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void isr_txeom(SLMP_INFO * info, unsigned char status)
{
	if ( debug_level >= DEBUG_LEVEL_ISR )
		printk("%s(%d):%s isr_txeom status=%02x\n",
			__FILE__,__LINE__,info->device_name,status);

	write_reg(info, TXDMA + DIR, 0x00); /* disable Tx DMA IRQs */
	write_reg(info, TXDMA + DSR, 0xc0); /* clear IRQs and disable DMA */
	write_reg(info, TXDMA + DCMD, SWABORT);	/* reset/init DMA channel */

	if (status & UDRN) {
		write_reg(info, CMD, TXRESET);
		write_reg(info, CMD, TXENABLE);
	} else
		write_reg(info, CMD, TXBUFCLR);

	/* disable and clear tx interrupts */
	info->ie0_value &= ~TXRDYE;
	info->ie1_value &= ~(IDLE + UDRN);
	write_reg16(info, IE0, (unsigned short)((info->ie1_value << 8) + info->ie0_value));
	write_reg(info, SR1, (unsigned char)(UDRN + IDLE));

	if ( info->tx_active ) {
		if (info->params.mode != MGSL_MODE_ASYNC) {
			if (status & UDRN)
				info->icount.txunder++;
			else if (status & IDLE)
				info->icount.txok++;
		}

		info->tx_active = false;
		info->tx_count = info->tx_put = info->tx_get = 0;

		del_timer(&info->tx_timer);

		if (info->params.mode != MGSL_MODE_ASYNC && info->drop_rts_on_tx_done ) {
			info->serial_signals &= ~SerialSignal_RTS;
			info->drop_rts_on_tx_done = false;
			set_signals(info);
		}

#if SYNCLINK_GENERIC_HDLC
		if (info->netcount)
			hdlcdev_tx_done(info);
		else
#endif
		{
			if (info->port.tty && (info->port.tty->stopped || info->port.tty->hw_stopped)) {
				tx_stop(info);
				return;
			}
			info->pending_bh |= BH_TRANSMIT;
		}
	}
}