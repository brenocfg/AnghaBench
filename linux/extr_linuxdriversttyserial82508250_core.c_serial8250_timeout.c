#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* handle_irq ) (TYPE_1__*) ;} ;
struct uart_8250_port {TYPE_1__ port; int /*<<< orphan*/  timer; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 struct uart_8250_port* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  timer ; 
 scalar_t__ uart_poll_timeout (TYPE_1__*) ; 
 struct uart_8250_port* up ; 

__attribute__((used)) static void serial8250_timeout(struct timer_list *t)
{
	struct uart_8250_port *up = from_timer(up, t, timer);

	up->port.handle_irq(&up->port);
	mod_timer(&up->timer, jiffies + uart_poll_timeout(&up->port));
}