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
struct tty_struct {struct port* driver_data; } ;
struct port {int /*<<< orphan*/  fifo_ul; } ;
struct nozomi {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 struct nozomi* get_dc_by_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  kfifo_len (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static s32 ntty_chars_in_buffer(struct tty_struct *tty)
{
	struct port *port = tty->driver_data;
	struct nozomi *dc = get_dc_by_tty(tty);
	s32 rval = 0;

	if (unlikely(!dc || !port)) {
		goto exit_in_buffer;
	}

	rval = kfifo_len(&port->fifo_ul);

exit_in_buffer:
	return rval;
}