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
struct tty_struct {int /*<<< orphan*/  port; } ;
struct tty_driver {int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 struct tty_struct* ERR_CAST (struct tty_struct*) ; 
 struct tty_struct* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct tty_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_driver_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_driver_lookup_tty (struct tty_struct*,int /*<<< orphan*/ *,int) ; 
 struct tty_struct* tty_init_dev (struct tty_struct*,int) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_lookup_driver (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  tty_mutex ; 
 int /*<<< orphan*/  tty_port_set_kopened (int /*<<< orphan*/ ,int) ; 

struct tty_struct *tty_kopen(dev_t device)
{
	struct tty_struct *tty;
	struct tty_driver *driver = NULL;
	int index = -1;

	mutex_lock(&tty_mutex);
	driver = tty_lookup_driver(device, NULL, &index);
	if (IS_ERR(driver)) {
		mutex_unlock(&tty_mutex);
		return ERR_CAST(driver);
	}

	/* check whether we're reopening an existing tty */
	tty = tty_driver_lookup_tty(driver, NULL, index);
	if (IS_ERR(tty))
		goto out;

	if (tty) {
		/* drop kref from tty_driver_lookup_tty() */
		tty_kref_put(tty);
		tty = ERR_PTR(-EBUSY);
	} else { /* tty_init_dev returns tty with the tty_lock held */
		tty = tty_init_dev(driver, index);
		if (IS_ERR(tty))
			goto out;
		tty_port_set_kopened(tty->port, 1);
	}
out:
	mutex_unlock(&tty_mutex);
	tty_driver_kref_put(driver);
	return tty;
}