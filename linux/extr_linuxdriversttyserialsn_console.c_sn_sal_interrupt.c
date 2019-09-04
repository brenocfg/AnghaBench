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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct sn_cons_port {TYPE_1__ sc_port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int SAL_CONSOLE_INTR_RECV ; 
 int SAL_CONSOLE_INTR_XMIT ; 
 int /*<<< orphan*/  TRANSMIT_BUFFERED ; 
 int ia64_sn_console_intr_status () ; 
 int /*<<< orphan*/  sn_receive_chars (struct sn_cons_port*,unsigned long) ; 
 int /*<<< orphan*/  sn_transmit_chars (struct sn_cons_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t sn_sal_interrupt(int irq, void *dev_id)
{
	struct sn_cons_port *port = (struct sn_cons_port *)dev_id;
	unsigned long flags;
	int status = ia64_sn_console_intr_status();

	if (!port)
		return IRQ_NONE;

	spin_lock_irqsave(&port->sc_port.lock, flags);
	if (status & SAL_CONSOLE_INTR_RECV) {
		sn_receive_chars(port, flags);
	}
	if (status & SAL_CONSOLE_INTR_XMIT) {
		sn_transmit_chars(port, TRANSMIT_BUFFERED);
	}
	spin_unlock_irqrestore(&port->sc_port.lock, flags);
	return IRQ_HANDLED;
}