#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {TYPE_2__* tty; } ;
struct mgsl_struct {int serial_signals; TYPE_3__ port; int /*<<< orphan*/  irq_spinlock; int /*<<< orphan*/ * xmit_buf; int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  event_wait_q; int /*<<< orphan*/  status_event_wait_q; int /*<<< orphan*/  device_name; } ;
struct TYPE_5__ {int c_cflag; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; TYPE_1__ termios; } ;

/* Variables and functions */
 int BIT12 ; 
 int BIT13 ; 
 int BIT14 ; 
 int BIT15 ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ DICR_MASTER ; 
 scalar_t__ DICR_RECEIVE ; 
 scalar_t__ DICR_TRANSMIT ; 
 int HUPCL ; 
 int IO_PIN ; 
 int MISC ; 
 int /*<<< orphan*/  PCR ; 
 int RECEIVE_DATA ; 
 int RECEIVE_STATUS ; 
 int SerialSignal_DTR ; 
 int SerialSignal_RTS ; 
 int TRANSMIT_DATA ; 
 int TRANSMIT_STATUS ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  mgsl_release_resources (struct mgsl_struct*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_port_initialized (TYPE_3__*) ; 
 int /*<<< orphan*/  tty_port_set_initialized (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_DisableDmaInterrupts (struct mgsl_struct*,scalar_t__) ; 
 int /*<<< orphan*/  usc_DisableInterrupts (struct mgsl_struct*,int) ; 
 int /*<<< orphan*/  usc_DisableMasterIrqBit (struct mgsl_struct*) ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_set_serial_signals (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_stop_receiver (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_stop_transmitter (struct mgsl_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shutdown(struct mgsl_struct * info)
{
	unsigned long flags;

	if (!tty_port_initialized(&info->port))
		return;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgsl_shutdown(%s)\n",
			 __FILE__,__LINE__, info->device_name );

	/* clear status wait queue because status changes */
	/* can't happen after shutting down the hardware */
	wake_up_interruptible(&info->status_event_wait_q);
	wake_up_interruptible(&info->event_wait_q);

	del_timer_sync(&info->tx_timer);

	if (info->xmit_buf) {
		free_page((unsigned long) info->xmit_buf);
		info->xmit_buf = NULL;
	}

	spin_lock_irqsave(&info->irq_spinlock,flags);
	usc_DisableMasterIrqBit(info);
	usc_stop_receiver(info);
	usc_stop_transmitter(info);
	usc_DisableInterrupts(info,RECEIVE_DATA | RECEIVE_STATUS |
		TRANSMIT_DATA | TRANSMIT_STATUS | IO_PIN | MISC );
	usc_DisableDmaInterrupts(info,DICR_MASTER + DICR_TRANSMIT + DICR_RECEIVE);

	/* Disable DMAEN (Port 7, Bit 14) */
	/* This disconnects the DMA request signal from the ISA bus */
	/* on the ISA adapter. This has no effect for the PCI adapter */
	usc_OutReg(info, PCR, (u16)((usc_InReg(info, PCR) | BIT15) | BIT14));

	/* Disable INTEN (Port 6, Bit12) */
	/* This disconnects the IRQ request signal to the ISA bus */
	/* on the ISA adapter. This has no effect for the PCI adapter */
	usc_OutReg(info, PCR, (u16)((usc_InReg(info, PCR) | BIT13) | BIT12));

	if (!info->port.tty || info->port.tty->termios.c_cflag & HUPCL) {
		info->serial_signals &= ~(SerialSignal_RTS | SerialSignal_DTR);
		usc_set_serial_signals(info);
	}

	spin_unlock_irqrestore(&info->irq_spinlock,flags);

	mgsl_release_resources(info);

	if (info->port.tty)
		set_bit(TTY_IO_ERROR, &info->port.tty->flags);

	tty_port_set_initialized(&info->port, 0);
}