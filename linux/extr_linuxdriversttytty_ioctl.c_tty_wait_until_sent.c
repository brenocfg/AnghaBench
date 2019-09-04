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
struct tty_struct {TYPE_1__* ops; int /*<<< orphan*/  write_wait; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* wait_until_sent ) (struct tty_struct*,long) ;} ;

/* Variables and functions */
 long MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*,long) ; 
 int /*<<< orphan*/  tty_chars_in_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_debug_wait_until_sent (struct tty_struct*,char*,long) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,long) ; 

void tty_wait_until_sent(struct tty_struct *tty, long timeout)
{
	tty_debug_wait_until_sent(tty, "wait until sent, timeout=%ld\n", timeout);

	if (!timeout)
		timeout = MAX_SCHEDULE_TIMEOUT;

	timeout = wait_event_interruptible_timeout(tty->write_wait,
			!tty_chars_in_buffer(tty), timeout);
	if (timeout <= 0)
		return;

	if (timeout == MAX_SCHEDULE_TIMEOUT)
		timeout = 0;

	if (tty->ops->wait_until_sent)
		tty->ops->wait_until_sent(tty, timeout);
}