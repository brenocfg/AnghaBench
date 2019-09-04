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
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 

__attribute__((used)) static int omap8250_no_handle_irq(struct uart_port *port)
{
	/* IRQ has not been requested but handling irq? */
	WARN_ONCE(1, "Unexpected irq handling before port startup\n");
	return 0;
}