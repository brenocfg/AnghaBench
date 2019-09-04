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
struct zfcp_adapter {int /*<<< orphan*/  qdio; int /*<<< orphan*/  gs; int /*<<< orphan*/  ns_up_work; int /*<<< orphan*/  stat_work; int /*<<< orphan*/  scan_work; struct ccw_device* ccw_device; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct ccw_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_ccw_adapter_put (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_dbf_adapter_unregister (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_destroy_adapter_work_queue (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_erp_thread_kill (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_fc_wka_ports_force_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_qdio_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_scsi_adapter_unregister (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_sysfs_adapter_attrs ; 

void zfcp_adapter_unregister(struct zfcp_adapter *adapter)
{
	struct ccw_device *cdev = adapter->ccw_device;

	cancel_delayed_work_sync(&adapter->scan_work);
	cancel_work_sync(&adapter->stat_work);
	cancel_work_sync(&adapter->ns_up_work);
	zfcp_destroy_adapter_work_queue(adapter);

	zfcp_fc_wka_ports_force_offline(adapter->gs);
	zfcp_scsi_adapter_unregister(adapter);
	sysfs_remove_group(&cdev->dev.kobj, &zfcp_sysfs_adapter_attrs);

	zfcp_erp_thread_kill(adapter);
	zfcp_dbf_adapter_unregister(adapter);
	zfcp_qdio_destroy(adapter->qdio);

	zfcp_ccw_adapter_put(adapter); /* final put to release */
}