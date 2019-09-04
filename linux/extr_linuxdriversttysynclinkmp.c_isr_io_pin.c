#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct mgsl_icount {int /*<<< orphan*/  cts; int /*<<< orphan*/  dcd; int /*<<< orphan*/  dsr; int /*<<< orphan*/  rng; } ;
struct TYPE_13__ {int hw_stopped; } ;
struct TYPE_12__ {TYPE_8__* tty; int /*<<< orphan*/  open_wait; } ;
struct TYPE_10__ {int /*<<< orphan*/  cts_down; int /*<<< orphan*/  cts_up; int /*<<< orphan*/  dcd_down; int /*<<< orphan*/  dcd_up; int /*<<< orphan*/  dsr_down; int /*<<< orphan*/  dsr_up; int /*<<< orphan*/  ri_down; int /*<<< orphan*/  ri_up; } ;
struct TYPE_11__ {int /*<<< orphan*/  pending_bh; TYPE_6__ port; int /*<<< orphan*/  device_name; int /*<<< orphan*/  event_wait_q; int /*<<< orphan*/  status_event_wait_q; TYPE_1__ input_signal_events; int /*<<< orphan*/  ie1_value; int /*<<< orphan*/  cts_chkcount; int /*<<< orphan*/  dcd_chkcount; struct mgsl_icount icount; } ;
typedef  TYPE_2__ SLMP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BH_STATUS ; 
 int /*<<< orphan*/  BH_TRANSMIT ; 
 int /*<<< orphan*/  CCTS ; 
 int /*<<< orphan*/  CDCD ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 int /*<<< orphan*/  IE1 ; 
 scalar_t__ IO_PIN_SHUTDOWN_LIMIT ; 
 int MISCSTATUS_CTS_LATCHED ; 
 int MISCSTATUS_DCD_LATCHED ; 
 int MISCSTATUS_DSR_LATCHED ; 
 int MISCSTATUS_RI_LATCHED ; 
 int SerialSignal_CTS ; 
 int SerialSignal_DCD ; 
 int SerialSignal_DSR ; 
 int SerialSignal_RI ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  tty_hangup (TYPE_8__*) ; 
 scalar_t__ tty_port_check_carrier (TYPE_6__*) ; 
 scalar_t__ tty_port_cts_enabled (TYPE_6__*) ; 
 int /*<<< orphan*/  tx_start (TYPE_2__*) ; 
 int /*<<< orphan*/  tx_stop (TYPE_2__*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_reg (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isr_io_pin( SLMP_INFO *info, u16 status )
{
 	struct	mgsl_icount *icount;

	if ( debug_level >= DEBUG_LEVEL_ISR )
		printk("%s(%d):isr_io_pin status=%04X\n",
			__FILE__,__LINE__,status);

	if (status & (MISCSTATUS_CTS_LATCHED | MISCSTATUS_DCD_LATCHED |
	              MISCSTATUS_DSR_LATCHED | MISCSTATUS_RI_LATCHED) ) {
		icount = &info->icount;
		/* update input line counters */
		if (status & MISCSTATUS_RI_LATCHED) {
			icount->rng++;
			if ( status & SerialSignal_RI )
				info->input_signal_events.ri_up++;
			else
				info->input_signal_events.ri_down++;
		}
		if (status & MISCSTATUS_DSR_LATCHED) {
			icount->dsr++;
			if ( status & SerialSignal_DSR )
				info->input_signal_events.dsr_up++;
			else
				info->input_signal_events.dsr_down++;
		}
		if (status & MISCSTATUS_DCD_LATCHED) {
			if ((info->dcd_chkcount)++ >= IO_PIN_SHUTDOWN_LIMIT) {
				info->ie1_value &= ~CDCD;
				write_reg(info, IE1, info->ie1_value);
			}
			icount->dcd++;
			if (status & SerialSignal_DCD) {
				info->input_signal_events.dcd_up++;
			} else
				info->input_signal_events.dcd_down++;
#if SYNCLINK_GENERIC_HDLC
			if (info->netcount) {
				if (status & SerialSignal_DCD)
					netif_carrier_on(info->netdev);
				else
					netif_carrier_off(info->netdev);
			}
#endif
		}
		if (status & MISCSTATUS_CTS_LATCHED)
		{
			if ((info->cts_chkcount)++ >= IO_PIN_SHUTDOWN_LIMIT) {
				info->ie1_value &= ~CCTS;
				write_reg(info, IE1, info->ie1_value);
			}
			icount->cts++;
			if ( status & SerialSignal_CTS )
				info->input_signal_events.cts_up++;
			else
				info->input_signal_events.cts_down++;
		}
		wake_up_interruptible(&info->status_event_wait_q);
		wake_up_interruptible(&info->event_wait_q);

		if (tty_port_check_carrier(&info->port) &&
		     (status & MISCSTATUS_DCD_LATCHED) ) {
			if ( debug_level >= DEBUG_LEVEL_ISR )
				printk("%s CD now %s...", info->device_name,
				       (status & SerialSignal_DCD) ? "on" : "off");
			if (status & SerialSignal_DCD)
				wake_up_interruptible(&info->port.open_wait);
			else {
				if ( debug_level >= DEBUG_LEVEL_ISR )
					printk("doing serial hangup...");
				if (info->port.tty)
					tty_hangup(info->port.tty);
			}
		}

		if (tty_port_cts_enabled(&info->port) &&
		     (status & MISCSTATUS_CTS_LATCHED) ) {
			if ( info->port.tty ) {
				if (info->port.tty->hw_stopped) {
					if (status & SerialSignal_CTS) {
						if ( debug_level >= DEBUG_LEVEL_ISR )
							printk("CTS tx start...");
			 			info->port.tty->hw_stopped = 0;
						tx_start(info);
						info->pending_bh |= BH_TRANSMIT;
						return;
					}
				} else {
					if (!(status & SerialSignal_CTS)) {
						if ( debug_level >= DEBUG_LEVEL_ISR )
							printk("CTS tx stop...");
			 			info->port.tty->hw_stopped = 1;
						tx_stop(info);
					}
				}
			}
		}
	}

	info->pending_bh |= BH_STATUS;
}