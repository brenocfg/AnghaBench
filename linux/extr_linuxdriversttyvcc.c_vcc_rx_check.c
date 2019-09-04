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
struct tty_struct {int /*<<< orphan*/  port; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_THROTTLED ; 
 scalar_t__ VCC_BUFF_LEN ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ tty_buffer_request_room (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int vcc_rx_check(struct tty_struct *tty, int size)
{
	if (WARN_ON(!tty || !tty->port))
		return 1;

	/* tty_buffer_request_room won't sleep because it uses
	 * GFP_ATOMIC flag to allocate buffer
	 */
	if (test_bit(TTY_THROTTLED, &tty->flags) ||
	    (tty_buffer_request_room(tty->port, VCC_BUFF_LEN) < VCC_BUFF_LEN))
		return 0;

	return 1;
}