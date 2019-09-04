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
struct uart_state {int /*<<< orphan*/  port; } ;
struct TYPE_2__ {int rx; } ;
struct uart_port {int /*<<< orphan*/  lock; TYPE_1__ icount; struct uart_state* state; } ;
struct ioc3_port {int ip_flags; } ;

/* Variables and functions */
 int INPUT_ENABLE ; 
 int MAX_CHARS ; 
 int do_read (struct uart_port*,unsigned char*,int) ; 
 struct ioc3_port* get_ioc3_port (struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int tty_insert_flip_string (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static int receive_chars(struct uart_port *the_port)
{
	unsigned char ch[MAX_CHARS];
	int read_count = 0, read_room, flip = 0;
	struct uart_state *state = the_port->state;
	struct ioc3_port *port = get_ioc3_port(the_port);
	unsigned long pflags;

	/* Make sure all the pointers are "good" ones */
	if (!state)
		return 0;

	if (!(port->ip_flags & INPUT_ENABLE))
		return 0;

	spin_lock_irqsave(&the_port->lock, pflags);

	read_count = do_read(the_port, ch, MAX_CHARS);
	if (read_count > 0) {
		flip = 1;
		read_room = tty_insert_flip_string(&state->port, ch,
				read_count);
		the_port->icount.rx += read_count;
	}
	spin_unlock_irqrestore(&the_port->lock, pflags);

	if (flip)
		tty_flip_buffer_push(&state->port);

	return read_count;
}