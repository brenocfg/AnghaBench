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
struct zfcp_adapter {int /*<<< orphan*/  scan_work; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_RUNNING ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 struct zfcp_adapter* zfcp_ccw_adapter_by_cdev (struct ccw_device*) ; 
 int /*<<< orphan*/  zfcp_ccw_adapter_put (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (struct zfcp_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfcp_erp_clear_adapter_status (struct zfcp_adapter*,int) ; 
 int /*<<< orphan*/  zfcp_erp_set_adapter_status (struct zfcp_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_wait (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_fc_port_scan_backoff () ; 

__attribute__((used)) static int zfcp_ccw_activate(struct ccw_device *cdev, int clear, char *tag)
{
	struct zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(cdev);

	if (!adapter)
		return 0;

	zfcp_erp_clear_adapter_status(adapter, clear);
	zfcp_erp_set_adapter_status(adapter, ZFCP_STATUS_COMMON_RUNNING);
	zfcp_erp_adapter_reopen(adapter, ZFCP_STATUS_COMMON_ERP_FAILED,
				tag);

	/*
	 * We want to scan ports here, with some random backoff and without
	 * rate limit. Recovery has already scheduled a port scan for us,
	 * but with both random delay and rate limit. Nevertheless we get
	 * what we want here by flushing the scheduled work after sleeping
	 * an equivalent random time.
	 * Let the port scan random delay elapse first. If recovery finishes
	 * up to that point in time, that would be perfect for both recovery
	 * and port scan. If not, i.e. recovery takes ages, there was no
	 * point in waiting a random delay on top of the time consumed by
	 * recovery.
	 */
	msleep(zfcp_fc_port_scan_backoff());
	zfcp_erp_wait(adapter);
	flush_delayed_work(&adapter->scan_work);

	zfcp_ccw_adapter_put(adapter);

	return 0;
}