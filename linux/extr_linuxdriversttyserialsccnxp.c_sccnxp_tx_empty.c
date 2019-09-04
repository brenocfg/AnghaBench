#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct uart_port {int /*<<< orphan*/  dev; } ;
struct sccnxp_port {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCCNXP_SR_REG ; 
 int SR_TXEMT ; 
 unsigned int TIOCSER_TEMT ; 
 struct sccnxp_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int sccnxp_port_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int sccnxp_tx_empty(struct uart_port *port)
{
	u8 val;
	unsigned long flags;
	struct sccnxp_port *s = dev_get_drvdata(port->dev);

	spin_lock_irqsave(&s->lock, flags);
	val = sccnxp_port_read(port, SCCNXP_SR_REG);
	spin_unlock_irqrestore(&s->lock, flags);

	return (val & SR_TXEMT) ? TIOCSER_TEMT : 0;
}