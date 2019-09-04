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
struct fw_mgmt {int disabled; int /*<<< orphan*/  node; int /*<<< orphan*/  connection; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev_num; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_mgmt_class ; 
 int /*<<< orphan*/  fw_mgmt_minors_map ; 
 int /*<<< orphan*/  gb_connection_disable (int /*<<< orphan*/ ) ; 
 struct fw_mgmt* gb_connection_get_data (struct gb_connection*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_fw_mgmt (struct fw_mgmt*) ; 

void gb_fw_mgmt_connection_exit(struct gb_connection *connection)
{
	struct fw_mgmt *fw_mgmt;

	if (!connection)
		return;

	fw_mgmt = gb_connection_get_data(connection);

	device_destroy(fw_mgmt_class, fw_mgmt->dev_num);
	cdev_del(&fw_mgmt->cdev);
	ida_simple_remove(&fw_mgmt_minors_map, MINOR(fw_mgmt->dev_num));

	/*
	 * Disallow any new ioctl operations on the char device and wait for
	 * existing ones to finish.
	 */
	mutex_lock(&fw_mgmt->mutex);
	fw_mgmt->disabled = true;
	mutex_unlock(&fw_mgmt->mutex);

	/* All pending greybus operations should have finished by now */
	gb_connection_disable(fw_mgmt->connection);

	/* Disallow new users to get access to the fw_mgmt structure */
	mutex_lock(&list_mutex);
	list_del(&fw_mgmt->node);
	mutex_unlock(&list_mutex);

	/*
	 * All current users of fw_mgmt would have taken a reference to it by
	 * now, we can drop our reference and wait the last user will get
	 * fw_mgmt freed.
	 */
	put_fw_mgmt(fw_mgmt);
}