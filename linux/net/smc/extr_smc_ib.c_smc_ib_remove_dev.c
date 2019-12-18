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
struct smc_ib_device {int /*<<< orphan*/  event_handler; int /*<<< orphan*/  list; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct smc_ib_device* ib_get_client_data (struct ib_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_event_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct smc_ib_device*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_ib_cleanup_per_ibdev (struct smc_ib_device*) ; 
 int /*<<< orphan*/  smc_ib_client ; 
 TYPE_1__ smc_ib_devices ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smc_ib_remove_dev(struct ib_device *ibdev, void *client_data)
{
	struct smc_ib_device *smcibdev;

	smcibdev = ib_get_client_data(ibdev, &smc_ib_client);
	ib_set_client_data(ibdev, &smc_ib_client, NULL);
	spin_lock(&smc_ib_devices.lock);
	list_del_init(&smcibdev->list); /* remove from smc_ib_devices */
	spin_unlock(&smc_ib_devices.lock);
	smc_ib_cleanup_per_ibdev(smcibdev);
	ib_unregister_event_handler(&smcibdev->event_handler);
	kfree(smcibdev);
}