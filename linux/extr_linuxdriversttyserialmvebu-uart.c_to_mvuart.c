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
struct uart_port {scalar_t__ private_data; } ;
struct mvebu_uart {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct mvebu_uart *to_mvuart(struct uart_port *port)
{
	return (struct mvebu_uart *)port->private_data;
}