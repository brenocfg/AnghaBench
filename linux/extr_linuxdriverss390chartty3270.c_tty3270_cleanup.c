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
struct tty_struct {struct tty3270* driver_data; } ;
struct tty3270 {int /*<<< orphan*/  view; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw3270_put_view (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tty3270_cleanup(struct tty_struct *tty)
{
	struct tty3270 *tp = tty->driver_data;

	if (tp) {
		tty->driver_data = NULL;
		raw3270_put_view(&tp->view);
	}
}