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
struct gb_tty {int /*<<< orphan*/  mutex; int /*<<< orphan*/  port; scalar_t__ disconnected; } ;

/* Variables and functions */
 struct gb_tty* idr_find (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_lock ; 
 int /*<<< orphan*/  tty_minors ; 
 int /*<<< orphan*/  tty_port_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct gb_tty *get_gb_by_minor(unsigned int minor)
{
	struct gb_tty *gb_tty;

	mutex_lock(&table_lock);
	gb_tty = idr_find(&tty_minors, minor);
	if (gb_tty) {
		mutex_lock(&gb_tty->mutex);
		if (gb_tty->disconnected) {
			mutex_unlock(&gb_tty->mutex);
			gb_tty = NULL;
		} else {
			tty_port_get(&gb_tty->port);
			mutex_unlock(&gb_tty->mutex);
		}
	}
	mutex_unlock(&table_lock);
	return gb_tty;
}