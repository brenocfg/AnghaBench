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
struct uart_port {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_ms ) (struct uart_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 

__attribute__((used)) static void uart_enable_ms(struct uart_port *uport)
{
	/*
	 * Force modem status interrupts on
	 */
	if (uport->ops->enable_ms)
		uport->ops->enable_ms(uport);
}