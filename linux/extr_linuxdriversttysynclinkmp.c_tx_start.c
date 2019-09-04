#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ mode; int flags; } ;
struct TYPE_12__ {int tx_enabled; int drop_rts_on_tx_done; int serial_signals; size_t last_tx_buf; int ie1_value; int ie0_value; int tx_active; int /*<<< orphan*/  tx_timer; TYPE_2__* tx_buf_list_ex; TYPE_1__ params; scalar_t__ tx_count; int /*<<< orphan*/  device_name; } ;
struct TYPE_11__ {unsigned short phys_entry; } ;
typedef  TYPE_3__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ CDA ; 
 scalar_t__ CMD ; 
 scalar_t__ DCMD ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 scalar_t__ DIR ; 
 scalar_t__ DSR ; 
 scalar_t__ EDA ; 
 int HDLC_FLAG_AUTO_RTS ; 
 int IDLE ; 
 scalar_t__ IE0 ; 
 scalar_t__ IE1 ; 
 scalar_t__ MGSL_MODE_ASYNC ; 
 scalar_t__ SR1 ; 
 int SWABORT ; 
 int SerialSignal_RTS ; 
 scalar_t__ TRC0 ; 
 scalar_t__ TXDMA ; 
 int TXENABLE ; 
 int TXRDYE ; 
 int TXRESET ; 
 int UDRN ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  get_signals (TYPE_3__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_signals (TYPE_3__*) ; 
 scalar_t__ tx_active_fifo_level ; 
 int /*<<< orphan*/  tx_load_fifo (TYPE_3__*) ; 
 int tx_negate_fifo_level ; 
 int /*<<< orphan*/  write_reg (TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  write_reg16 (TYPE_3__*,scalar_t__,unsigned short) ; 

__attribute__((used)) static void tx_start(SLMP_INFO *info)
{
	if (debug_level >= DEBUG_LEVEL_ISR)
		printk("%s(%d):%s tx_start() tx_count=%d\n",
			 __FILE__,__LINE__, info->device_name,info->tx_count );

	if (!info->tx_enabled ) {
		write_reg(info, CMD, TXRESET);
		write_reg(info, CMD, TXENABLE);
		info->tx_enabled = true;
	}

	if ( info->tx_count ) {

		/* If auto RTS enabled and RTS is inactive, then assert */
		/* RTS and set a flag indicating that the driver should */
		/* negate RTS when the transmission completes. */

		info->drop_rts_on_tx_done = false;

		if (info->params.mode != MGSL_MODE_ASYNC) {

			if ( info->params.flags & HDLC_FLAG_AUTO_RTS ) {
				get_signals( info );
				if ( !(info->serial_signals & SerialSignal_RTS) ) {
					info->serial_signals |= SerialSignal_RTS;
					set_signals( info );
					info->drop_rts_on_tx_done = true;
				}
			}

			write_reg16(info, TRC0,
				(unsigned short)(((tx_negate_fifo_level-1)<<8) + tx_active_fifo_level));

			write_reg(info, TXDMA + DSR, 0); 		/* disable DMA channel */
			write_reg(info, TXDMA + DCMD, SWABORT);	/* reset/init DMA channel */
	
			/* set TX CDA (current descriptor address) */
			write_reg16(info, TXDMA + CDA,
				info->tx_buf_list_ex[0].phys_entry);
	
			/* set TX EDA (last descriptor address) */
			write_reg16(info, TXDMA + EDA,
				info->tx_buf_list_ex[info->last_tx_buf].phys_entry);
	
			/* enable underrun IRQ */
			info->ie1_value &= ~IDLE;
			info->ie1_value |= UDRN;
			write_reg(info, IE1, info->ie1_value);
			write_reg(info, SR1, (unsigned char)(IDLE + UDRN));
	
			write_reg(info, TXDMA + DIR, 0x40);		/* enable Tx DMA interrupts (EOM) */
			write_reg(info, TXDMA + DSR, 0xf2);		/* clear Tx DMA IRQs, enable Tx DMA */
	
			mod_timer(&info->tx_timer, jiffies +
					msecs_to_jiffies(5000));
		}
		else {
			tx_load_fifo(info);
			/* async, enable IRQ on txdata */
			info->ie0_value |= TXRDYE;
			write_reg(info, IE0, info->ie0_value);
		}

		info->tx_active = true;
	}
}