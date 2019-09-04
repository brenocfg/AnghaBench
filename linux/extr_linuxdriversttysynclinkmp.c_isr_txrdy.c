#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* tty; } ;
struct TYPE_10__ {scalar_t__ mode; } ;
struct TYPE_13__ {scalar_t__ tx_count; int ie0_value; int ie1_value; int tx_active; int /*<<< orphan*/  pending_bh; TYPE_3__ port; TYPE_1__ params; int /*<<< orphan*/  device_name; } ;
struct TYPE_11__ {scalar_t__ hw_stopped; scalar_t__ stopped; } ;
typedef  TYPE_4__ SLMP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BH_TRANSMIT ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 int IDLE ; 
 int /*<<< orphan*/  IE0 ; 
 scalar_t__ MGSL_MODE_ASYNC ; 
 int TXRDYE ; 
 scalar_t__ WAKEUP_CHARS ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tx_load_fifo (TYPE_4__*) ; 
 int /*<<< orphan*/  tx_stop (TYPE_4__*) ; 
 int /*<<< orphan*/  write_reg (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_reg16 (TYPE_4__*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void isr_txrdy(SLMP_INFO * info)
{
	if ( debug_level >= DEBUG_LEVEL_ISR )
		printk("%s(%d):%s isr_txrdy() tx_count=%d\n",
			__FILE__,__LINE__,info->device_name,info->tx_count);

	if (info->params.mode != MGSL_MODE_ASYNC) {
		/* disable TXRDY IRQ, enable IDLE IRQ */
		info->ie0_value &= ~TXRDYE;
		info->ie1_value |= IDLE;
		write_reg16(info, IE0, (unsigned short)((info->ie1_value << 8) + info->ie0_value));
		return;
	}

	if (info->port.tty && (info->port.tty->stopped || info->port.tty->hw_stopped)) {
		tx_stop(info);
		return;
	}

	if ( info->tx_count )
		tx_load_fifo( info );
	else {
		info->tx_active = false;
		info->ie0_value &= ~TXRDYE;
		write_reg(info, IE0, info->ie0_value);
	}

	if (info->tx_count < WAKEUP_CHARS)
		info->pending_bh |= BH_TRANSMIT;
}