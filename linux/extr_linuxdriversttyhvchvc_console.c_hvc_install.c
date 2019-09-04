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
struct tty_struct {struct hvc_struct* driver_data; int /*<<< orphan*/  index; } ;
struct tty_driver {int dummy; } ;
struct hvc_struct {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int ENODEV ; 
 struct hvc_struct* hvc_get_by_index (int /*<<< orphan*/ ) ; 
 int tty_port_install (int /*<<< orphan*/ *,struct tty_driver*,struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hvc_install(struct tty_driver *driver, struct tty_struct *tty)
{
	struct hvc_struct *hp;
	int rc;

	/* Auto increments kref reference if found. */
	hp = hvc_get_by_index(tty->index);
	if (!hp)
		return -ENODEV;

	tty->driver_data = hp;

	rc = tty_port_install(&hp->port, driver, tty);
	if (rc)
		tty_port_put(&hp->port);
	return rc;
}