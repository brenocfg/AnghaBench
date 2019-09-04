#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct gsm_mux {TYPE_2__* tty; } ;
struct TYPE_5__ {TYPE_1__* ops; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* write ) (TYPE_2__*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int ENOSPC ; 
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 int debug ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int tty_write_room (TYPE_2__*) ; 

__attribute__((used)) static int gsmld_output(struct gsm_mux *gsm, u8 *data, int len)
{
	if (tty_write_room(gsm->tty) < len) {
		set_bit(TTY_DO_WRITE_WAKEUP, &gsm->tty->flags);
		return -ENOSPC;
	}
	if (debug & 4)
		print_hex_dump_bytes("gsmld_output: ", DUMP_PREFIX_OFFSET,
				     data, len);
	gsm->tty->ops->write(gsm->tty, data, len);
	return len;
}