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
struct ktermios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_termios_copy_hw (struct ktermios*,struct ktermios*) ; 

__attribute__((used)) static void altera_jtaguart_set_termios(struct uart_port *port,
					struct ktermios *termios,
					struct ktermios *old)
{
	/* Just copy the old termios settings back */
	if (old)
		tty_termios_copy_hw(termios, old);
}