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
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  mctrl; int /*<<< orphan*/  line; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  irqflags; } ;
struct uart_omap_port {int ier; int wer; int features; int /*<<< orphan*/  port_activity; int /*<<< orphan*/  dev; scalar_t__ msr_saved_flags; TYPE_1__ port; scalar_t__ wakeirq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int OMAP_UART_TX_WAKEUP_EN ; 
 int OMAP_UART_WER_HAS_TX_WAKEUP ; 
 int OMAP_UART_WER_MOD_WKUP ; 
 int /*<<< orphan*/  TIOCM_OUT2 ; 
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 int /*<<< orphan*/  UART_IIR ; 
 int /*<<< orphan*/  UART_LCR ; 
 int UART_LCR_WLEN8 ; 
 int /*<<< orphan*/  UART_LSR ; 
 int UART_LSR_DR ; 
 int /*<<< orphan*/  UART_MSR ; 
 int /*<<< orphan*/  UART_OMAP_WER ; 
 int /*<<< orphan*/  UART_RX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int dev_pm_set_dedicated_wake_irq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_omap_port*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uart_omap_port*) ; 
 int serial_in (struct uart_omap_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_omap_clear_fifos (struct uart_omap_port*) ; 
 int /*<<< orphan*/  serial_omap_irq ; 
 int /*<<< orphan*/  serial_omap_set_mctrl (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_omap_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uart_omap_port* to_uart_omap_port (struct uart_port*) ; 

__attribute__((used)) static int serial_omap_startup(struct uart_port *port)
{
	struct uart_omap_port *up = to_uart_omap_port(port);
	unsigned long flags = 0;
	int retval;

	/*
	 * Allocate the IRQ
	 */
	retval = request_irq(up->port.irq, serial_omap_irq, up->port.irqflags,
				up->name, up);
	if (retval)
		return retval;

	/* Optional wake-up IRQ */
	if (up->wakeirq) {
		retval = dev_pm_set_dedicated_wake_irq(up->dev, up->wakeirq);
		if (retval) {
			free_irq(up->port.irq, up);
			return retval;
		}
	}

	dev_dbg(up->port.dev, "serial_omap_startup+%d\n", up->port.line);

	pm_runtime_get_sync(up->dev);
	/*
	 * Clear the FIFO buffers and disable them.
	 * (they will be reenabled in set_termios())
	 */
	serial_omap_clear_fifos(up);

	/*
	 * Clear the interrupt registers.
	 */
	(void) serial_in(up, UART_LSR);
	if (serial_in(up, UART_LSR) & UART_LSR_DR)
		(void) serial_in(up, UART_RX);
	(void) serial_in(up, UART_IIR);
	(void) serial_in(up, UART_MSR);

	/*
	 * Now, initialize the UART
	 */
	serial_out(up, UART_LCR, UART_LCR_WLEN8);
	spin_lock_irqsave(&up->port.lock, flags);
	/*
	 * Most PC uarts need OUT2 raised to enable interrupts.
	 */
	up->port.mctrl |= TIOCM_OUT2;
	serial_omap_set_mctrl(&up->port, up->port.mctrl);
	spin_unlock_irqrestore(&up->port.lock, flags);

	up->msr_saved_flags = 0;
	/*
	 * Finally, enable interrupts. Note: Modem status interrupts
	 * are set via set_termios(), which will be occurring imminently
	 * anyway, so we don't enable them here.
	 */
	up->ier = UART_IER_RLSI | UART_IER_RDI;
	serial_out(up, UART_IER, up->ier);

	/* Enable module level wake up */
	up->wer = OMAP_UART_WER_MOD_WKUP;
	if (up->features & OMAP_UART_WER_HAS_TX_WAKEUP)
		up->wer |= OMAP_UART_TX_WAKEUP_EN;

	serial_out(up, UART_OMAP_WER, up->wer);

	pm_runtime_mark_last_busy(up->dev);
	pm_runtime_put_autosuspend(up->dev);
	up->port_activity = jiffies;
	return 0;
}