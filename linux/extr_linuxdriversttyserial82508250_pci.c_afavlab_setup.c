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
struct uart_8250_port {int dummy; } ;
struct serial_private {int dummy; } ;
struct pciserial_board {unsigned int first_offset; int uart_offset; int /*<<< orphan*/  reg_shift; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned int FL_GET_BASE (int /*<<< orphan*/ ) ; 
 int setup_port (struct serial_private*,struct uart_8250_port*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
afavlab_setup(struct serial_private *priv, const struct pciserial_board *board,
	      struct uart_8250_port *port, int idx)
{
	unsigned int bar, offset = board->first_offset;

	bar = FL_GET_BASE(board->flags);
	if (idx < 4)
		bar += idx;
	else {
		bar = 4;
		offset += (idx - 4) * board->uart_offset;
	}

	return setup_port(priv, port, bar, offset, board->reg_shift);
}