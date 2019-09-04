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
struct uart_8250_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  serial8250_clear_and_reinit_fifos (struct uart_8250_port*) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static void kt_handle_break(struct uart_port *p)
{
	struct uart_8250_port *up = up_to_u8250p(p);
	/*
	 * On receipt of a BI, serial device in Intel ME (Intel
	 * management engine) needs to have its fifos cleared for sane
	 * SOL (Serial Over Lan) output.
	 */
	serial8250_clear_and_reinit_fifos(up);
}