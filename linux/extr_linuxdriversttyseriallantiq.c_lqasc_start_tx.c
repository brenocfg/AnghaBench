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
 int /*<<< orphan*/  lqasc_tx_chars (struct uart_port*) ; 
 int /*<<< orphan*/  ltq_asc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
lqasc_start_tx(struct uart_port *port)
{
	unsigned long flags;
	spin_lock_irqsave(&ltq_asc_lock, flags);
	lqasc_tx_chars(port);
	spin_unlock_irqrestore(&ltq_asc_lock, flags);
	return;
}