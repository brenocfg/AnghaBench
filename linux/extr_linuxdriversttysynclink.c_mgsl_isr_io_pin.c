#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_6__ {TYPE_4__* tty; int /*<<< orphan*/  open_wait; } ;
struct TYPE_5__ {int /*<<< orphan*/  cts_down; int /*<<< orphan*/  cts_up; int /*<<< orphan*/  dcd_down; int /*<<< orphan*/  dcd_up; int /*<<< orphan*/  dsr_down; int /*<<< orphan*/  dsr_up; int /*<<< orphan*/  ri_down; int /*<<< orphan*/  ri_up; } ;
struct mgsl_icount {int /*<<< orphan*/  cts; int /*<<< orphan*/  dcd; int /*<<< orphan*/  dsr; int /*<<< orphan*/  rng; } ;
struct mgsl_struct {int irq_occurred; int /*<<< orphan*/  pending_bh; TYPE_2__ port; int /*<<< orphan*/  device_name; int /*<<< orphan*/  event_wait_q; int /*<<< orphan*/  status_event_wait_q; TYPE_1__ input_signal_events; int /*<<< orphan*/  cts_chkcount; int /*<<< orphan*/  dcd_chkcount; int /*<<< orphan*/  dsr_chkcount; int /*<<< orphan*/  ri_chkcount; struct mgsl_icount icount; } ;
struct TYPE_7__ {int hw_stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_STATUS ; 
 int /*<<< orphan*/  BH_TRANSMIT ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 int /*<<< orphan*/  IO_PIN ; 
 scalar_t__ IO_PIN_SHUTDOWN_LIMIT ; 
 int MISCSTATUS_CTS ; 
 int MISCSTATUS_CTS_LATCHED ; 
 int MISCSTATUS_DCD ; 
 int MISCSTATUS_DCD_LATCHED ; 
 int MISCSTATUS_DSR ; 
 int MISCSTATUS_DSR_LATCHED ; 
 int MISCSTATUS_RI ; 
 int MISCSTATUS_RI_LATCHED ; 
 int MISCSTATUS_TXC_LATCHED ; 
 int /*<<< orphan*/  MISR ; 
 int /*<<< orphan*/  SICR ; 
 int /*<<< orphan*/  SICR_CTS ; 
 int /*<<< orphan*/  SICR_DCD ; 
 int /*<<< orphan*/  SICR_DSR ; 
 int /*<<< orphan*/  SICR_RI ; 
 int SICR_TXC_ACTIVE ; 
 int SICR_TXC_INACTIVE ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  tty_hangup (TYPE_4__*) ; 
 scalar_t__ tty_port_check_carrier (TYPE_2__*) ; 
 scalar_t__ tty_port_cts_enabled (TYPE_2__*) ; 
 int /*<<< orphan*/  usc_ClearIrqPendingBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_DisablestatusIrqs (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  usc_UnlatchIostatusBits (struct mgsl_struct*,int) ; 
 int /*<<< orphan*/  usc_start_transmitter (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_stop_transmitter (struct mgsl_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mgsl_isr_io_pin( struct mgsl_struct *info )
{
 	struct	mgsl_icount *icount;
	u16 status = usc_InReg( info, MISR );

	if ( debug_level >= DEBUG_LEVEL_ISR )	
		printk("%s(%d):mgsl_isr_io_pin status=%04X\n",
			__FILE__,__LINE__,status);
			
	usc_ClearIrqPendingBits( info, IO_PIN );
	usc_UnlatchIostatusBits( info, status );

	if (status & (MISCSTATUS_CTS_LATCHED | MISCSTATUS_DCD_LATCHED |
	              MISCSTATUS_DSR_LATCHED | MISCSTATUS_RI_LATCHED) ) {
		icount = &info->icount;
		/* update input line counters */
		if (status & MISCSTATUS_RI_LATCHED) {
			if ((info->ri_chkcount)++ >= IO_PIN_SHUTDOWN_LIMIT)
				usc_DisablestatusIrqs(info,SICR_RI);
			icount->rng++;
			if ( status & MISCSTATUS_RI )
				info->input_signal_events.ri_up++;	
			else
				info->input_signal_events.ri_down++;	
		}
		if (status & MISCSTATUS_DSR_LATCHED) {
			if ((info->dsr_chkcount)++ >= IO_PIN_SHUTDOWN_LIMIT)
				usc_DisablestatusIrqs(info,SICR_DSR);
			icount->dsr++;
			if ( status & MISCSTATUS_DSR )
				info->input_signal_events.dsr_up++;
			else
				info->input_signal_events.dsr_down++;
		}
		if (status & MISCSTATUS_DCD_LATCHED) {
			if ((info->dcd_chkcount)++ >= IO_PIN_SHUTDOWN_LIMIT)
				usc_DisablestatusIrqs(info,SICR_DCD);
			icount->dcd++;
			if (status & MISCSTATUS_DCD) {
				info->input_signal_events.dcd_up++;
			} else
				info->input_signal_events.dcd_down++;
#if SYNCLINK_GENERIC_HDLC
			if (info->netcount) {
				if (status & MISCSTATUS_DCD)
					netif_carrier_on(info->netdev);
				else
					netif_carrier_off(info->netdev);
			}
#endif
		}
		if (status & MISCSTATUS_CTS_LATCHED)
		{
			if ((info->cts_chkcount)++ >= IO_PIN_SHUTDOWN_LIMIT)
				usc_DisablestatusIrqs(info,SICR_CTS);
			icount->cts++;
			if ( status & MISCSTATUS_CTS )
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
				       (status & MISCSTATUS_DCD) ? "on" : "off");
			if (status & MISCSTATUS_DCD)
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
			if (info->port.tty->hw_stopped) {
				if (status & MISCSTATUS_CTS) {
					if ( debug_level >= DEBUG_LEVEL_ISR )
						printk("CTS tx start...");
					info->port.tty->hw_stopped = 0;
					usc_start_transmitter(info);
					info->pending_bh |= BH_TRANSMIT;
					return;
				}
			} else {
				if (!(status & MISCSTATUS_CTS)) {
					if ( debug_level >= DEBUG_LEVEL_ISR )
						printk("CTS tx stop...");
					if (info->port.tty)
						info->port.tty->hw_stopped = 1;
					usc_stop_transmitter(info);
				}
			}
		}
	}

	info->pending_bh |= BH_STATUS;
	
	/* for diagnostics set IRQ flag */
	if ( status & MISCSTATUS_TXC_LATCHED ){
		usc_OutReg( info, SICR,
			(unsigned short)(usc_InReg(info,SICR) & ~(SICR_TXC_ACTIVE+SICR_TXC_INACTIVE)) );
		usc_UnlatchIostatusBits( info, MISCSTATUS_TXC_LATCHED );
		info->irq_occurred = true;
	}

}