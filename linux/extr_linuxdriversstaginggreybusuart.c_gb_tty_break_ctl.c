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
struct tty_struct {struct gb_tty* driver_data; } ;
struct gb_tty {int dummy; } ;

/* Variables and functions */
 int send_break (struct gb_tty*,int) ; 

__attribute__((used)) static int gb_tty_break_ctl(struct tty_struct *tty, int state)
{
	struct gb_tty *gb_tty = tty->driver_data;

	return send_break(gb_tty, state ? 1 : 0);
}