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
struct tty_struct {struct moxa_port* driver_data; } ;
struct moxa_port {int /*<<< orphan*/  statusflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTYWAIT ; 
 int MoxaPortTxQueue (struct moxa_port*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int moxa_chars_in_buffer(struct tty_struct *tty)
{
	struct moxa_port *ch = tty->driver_data;
	int chars;

	chars = MoxaPortTxQueue(ch);
	if (chars)
		/*
		 * Make it possible to wakeup anything waiting for output
		 * in tty_ioctl.c, etc.
		 */
        	set_bit(EMPTYWAIT, &ch->statusflags);
	return chars;
}