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
struct uart_sunzilog_port {unsigned int cflag; int* curregs; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int BPS_TO_BRG (int,int) ; 
 unsigned int CBAUD ; 
 size_t R12 ; 
 size_t R13 ; 
 int /*<<< orphan*/  ZILOG_CHANNEL_FROM_PORT (int /*<<< orphan*/ *) ; 
 int ZS_CLOCK ; 
 int ZS_CLOCK_DIVISOR ; 
 unsigned int suncore_mouse_baud_cflag_next (unsigned int,int*) ; 
 int /*<<< orphan*/  sunzilog_maybe_update_regs (struct uart_sunzilog_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sunzilog_change_mouse_baud(struct uart_sunzilog_port *up)
{
	unsigned int cur_cflag = up->cflag;
	int brg, new_baud;

	up->cflag &= ~CBAUD;
	up->cflag |= suncore_mouse_baud_cflag_next(cur_cflag, &new_baud);

	brg = BPS_TO_BRG(new_baud, ZS_CLOCK / ZS_CLOCK_DIVISOR);
	up->curregs[R12] = (brg & 0xff);
	up->curregs[R13] = (brg >> 8) & 0xff;
	sunzilog_maybe_update_regs(up, ZILOG_CHANNEL_FROM_PORT(&up->port));
}