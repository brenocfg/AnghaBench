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
struct tty_struct {int dummy; } ;
struct tty_dev {struct gdm** gdm; } ;
struct gdm {size_t index; size_t minor; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int TTY_MAX_COUNT ; 
 int /*<<< orphan*/ * gdm_driver ; 
 int /*<<< orphan*/ *** gdm_table ; 
 int /*<<< orphan*/  gdm_table_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_put (int /*<<< orphan*/ *) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  tty_vhangup (struct tty_struct*) ; 

void unregister_lte_tty_device(struct tty_dev *tty_dev)
{
	struct gdm *gdm;
	struct tty_struct *tty;
	int i;

	for (i = 0; i < TTY_MAX_COUNT; i++) {
		gdm = tty_dev->gdm[i];
		if (!gdm)
			continue;

		mutex_lock(&gdm_table_lock);
		gdm_table[gdm->index][gdm->minor] = NULL;
		mutex_unlock(&gdm_table_lock);

		tty = tty_port_tty_get(&gdm->port);
		if (tty) {
			tty_vhangup(tty);
			tty_kref_put(tty);
		}

		tty_unregister_device(gdm_driver[i], gdm->minor);
		tty_port_put(&gdm->port);
	}
}