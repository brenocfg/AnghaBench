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
struct tty_struct {int /*<<< orphan*/  receive_room; TYPE_1__* disc_data; } ;
struct TYPE_2__ {int opencalled; int /*<<< orphan*/ * kref_tty; } ;

/* Variables and functions */
 int EEXIST ; 
 int EFAULT ; 
 int /*<<< orphan*/  RECEIVE_ROOM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  routelock ; 
 TYPE_1__* tr_data ; 
 int /*<<< orphan*/  tty_driver_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/ * tty_kref_get (struct tty_struct*) ; 

__attribute__((used)) static int n_tracerouter_open(struct tty_struct *tty)
{
	int retval = -EEXIST;

	mutex_lock(&routelock);
	if (tr_data->opencalled == 0) {

		tr_data->kref_tty = tty_kref_get(tty);
		if (tr_data->kref_tty == NULL) {
			retval = -EFAULT;
		} else {
			tr_data->opencalled = 1;
			tty->disc_data      = tr_data;
			tty->receive_room   = RECEIVE_ROOM;
			tty_driver_flush_buffer(tty);
			retval = 0;
		}
	}
	mutex_unlock(&routelock);
	return retval;
}