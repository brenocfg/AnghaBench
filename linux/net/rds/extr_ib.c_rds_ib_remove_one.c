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
struct rds_ib_device {int /*<<< orphan*/  list; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_ib_client ; 
 int /*<<< orphan*/  rds_ib_dev_put (struct rds_ib_device*) ; 
 int /*<<< orphan*/  rds_ib_dev_shutdown (struct rds_ib_device*) ; 
 int /*<<< orphan*/  rds_ib_devices_lock ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rds_ib_remove_one(struct ib_device *device, void *client_data)
{
	struct rds_ib_device *rds_ibdev = client_data;

	if (!rds_ibdev)
		return;

	rds_ib_dev_shutdown(rds_ibdev);

	/* stop connection attempts from getting a reference to this device. */
	ib_set_client_data(device, &rds_ib_client, NULL);

	down_write(&rds_ib_devices_lock);
	list_del_rcu(&rds_ibdev->list);
	up_write(&rds_ib_devices_lock);

	/*
	 * This synchronize rcu is waiting for readers of both the ib
	 * client data and the devices list to finish before we drop
	 * both of those references.
	 */
	synchronize_rcu();
	rds_ib_dev_put(rds_ibdev);
	rds_ib_dev_put(rds_ibdev);
}