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
struct gb_connection {int dummy; } ;
struct gb_cap {int disabled; int /*<<< orphan*/  node; int /*<<< orphan*/  connection; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev_num; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_class ; 
 int /*<<< orphan*/  cap_minors_map ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_disable (int /*<<< orphan*/ ) ; 
 struct gb_cap* gb_connection_get_data (struct gb_connection*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_cap (struct gb_cap*) ; 

void gb_cap_connection_exit(struct gb_connection *connection)
{
	struct gb_cap *cap;

	if (!connection)
		return;

	cap = gb_connection_get_data(connection);

	device_destroy(cap_class, cap->dev_num);
	cdev_del(&cap->cdev);
	ida_simple_remove(&cap_minors_map, MINOR(cap->dev_num));

	/*
	 * Disallow any new ioctl operations on the char device and wait for
	 * existing ones to finish.
	 */
	mutex_lock(&cap->mutex);
	cap->disabled = true;
	mutex_unlock(&cap->mutex);

	/* All pending greybus operations should have finished by now */
	gb_connection_disable(cap->connection);

	/* Disallow new users to get access to the cap structure */
	mutex_lock(&list_mutex);
	list_del(&cap->node);
	mutex_unlock(&list_mutex);

	/*
	 * All current users of cap would have taken a reference to it by
	 * now, we can drop our reference and wait the last user will get
	 * cap freed.
	 */
	put_cap(cap);
}