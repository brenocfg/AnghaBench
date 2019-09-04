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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct sccnxp_port {int /*<<< orphan*/  lock; TYPE_1__* chip; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTR_OP ; 
 int /*<<< orphan*/  RTS_OP ; 
 int SCCNXP_HAVE_IO ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 struct sccnxp_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccnxp_set_bit (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sccnxp_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	struct sccnxp_port *s = dev_get_drvdata(port->dev);
	unsigned long flags;

	if (!(s->chip->flags & SCCNXP_HAVE_IO))
		return;

	spin_lock_irqsave(&s->lock, flags);

	sccnxp_set_bit(port, DTR_OP, mctrl & TIOCM_DTR);
	sccnxp_set_bit(port, RTS_OP, mctrl & TIOCM_RTS);

	spin_unlock_irqrestore(&s->lock, flags);
}