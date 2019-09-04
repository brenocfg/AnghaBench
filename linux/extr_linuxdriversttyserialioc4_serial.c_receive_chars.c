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
struct uart_state {int /*<<< orphan*/  port; } ;
struct uart_icount {int rx; } ;
struct uart_port {int /*<<< orphan*/  lock; struct uart_icount icount; struct uart_state* state; } ;

/* Variables and functions */
 int IOC4_MAX_CHARS ; 
 int do_read (struct uart_port*,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int tty_buffer_request_room (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_insert_flip_string (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static void receive_chars(struct uart_port *the_port)
{
	unsigned char ch[IOC4_MAX_CHARS];
	int read_count, request_count = IOC4_MAX_CHARS;
	struct uart_icount *icount;
	struct uart_state *state = the_port->state;
	unsigned long pflags;

	/* Make sure all the pointers are "good" ones */
	if (!state)
		return;

	spin_lock_irqsave(&the_port->lock, pflags);

	request_count = tty_buffer_request_room(&state->port, IOC4_MAX_CHARS);

	if (request_count > 0) {
		icount = &the_port->icount;
		read_count = do_read(the_port, ch, request_count);
		if (read_count > 0) {
			tty_insert_flip_string(&state->port, ch, read_count);
			icount->rx += read_count;
		}
	}

	spin_unlock_irqrestore(&the_port->lock, pflags);

	tty_flip_buffer_push(&state->port);
}