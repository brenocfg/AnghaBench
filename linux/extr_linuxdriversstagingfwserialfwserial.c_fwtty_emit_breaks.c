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
struct work_struct {int dummy; } ;
struct TYPE_2__ {int brk; } ;
struct fwtty_port {unsigned long break_last; unsigned long cps; int mstatus; TYPE_1__ icount; int /*<<< orphan*/  emit_breaks; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREQ_BREAKS ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  TTY_BREAK ; 
 int UART_LSR_BI ; 
 int /*<<< orphan*/  emit_breaks ; 
 int /*<<< orphan*/  fwtty_dbg (struct fwtty_port*,char*,int) ; 
 unsigned long jiffies ; 
 int min (int,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_delayed_work (struct work_struct*) ; 
 struct fwtty_port* to_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int tty_insert_flip_string_fixed_flag (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fwtty_emit_breaks(struct work_struct *work)
{
	struct fwtty_port *port = to_port(to_delayed_work(work), emit_breaks);
	static const char buf[16];
	unsigned long now = jiffies;
	unsigned long elapsed = now - port->break_last;
	int n, t, c, brk = 0;

	/* generate breaks at the line rate (but at least 1) */
	n = (elapsed * port->cps) / HZ + 1;
	port->break_last = now;

	fwtty_dbg(port, "sending %d brks\n", n);

	while (n) {
		t = min(n, 16);
		c = tty_insert_flip_string_fixed_flag(&port->port, buf,
						      TTY_BREAK, t);
		n -= c;
		brk += c;
		if (c < t)
			break;
	}
	tty_flip_buffer_push(&port->port);

	if (port->mstatus & (UART_LSR_BI << 24))
		schedule_delayed_work(&port->emit_breaks, FREQ_BREAKS);
	port->icount.brk += brk;
}