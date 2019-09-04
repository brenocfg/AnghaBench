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
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX310X_IRQSTS_REG ; 
 unsigned int MAX310X_IRQ_TXEMPTY_BIT ; 
 int /*<<< orphan*/  MAX310X_TXFIFOLVL_REG ; 
 unsigned int TIOCSER_TEMT ; 
 unsigned int max310x_port_read (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int max310x_tx_empty(struct uart_port *port)
{
	unsigned int lvl, sts;

	lvl = max310x_port_read(port, MAX310X_TXFIFOLVL_REG);
	sts = max310x_port_read(port, MAX310X_IRQSTS_REG);

	return ((sts & MAX310X_IRQ_TXEMPTY_BIT) && !lvl) ? TIOCSER_TEMT : 0;
}