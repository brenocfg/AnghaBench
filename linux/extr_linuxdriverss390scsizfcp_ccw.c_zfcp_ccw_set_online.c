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
struct zfcp_adapter {int /*<<< orphan*/  scan_work; scalar_t__ req_no; int /*<<< orphan*/  req_list; int /*<<< orphan*/  ref; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct zfcp_adapter*) ; 
 int PTR_ERR (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct zfcp_adapter* zfcp_adapter_enqueue (struct ccw_device*) ; 
 int /*<<< orphan*/  zfcp_ccw_activate (struct ccw_device*,int /*<<< orphan*/ ,char*) ; 
 struct zfcp_adapter* zfcp_ccw_adapter_by_cdev (struct ccw_device*) ; 
 int /*<<< orphan*/  zfcp_ccw_adapter_put (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_fc_inverse_conditional_port_scan (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_reqlist_isempty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zfcp_ccw_set_online(struct ccw_device *cdev)
{
	struct zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(cdev);

	if (!adapter) {
		adapter = zfcp_adapter_enqueue(cdev);

		if (IS_ERR(adapter)) {
			dev_err(&cdev->dev,
				"Setting up data structures for the "
				"FCP adapter failed\n");
			return PTR_ERR(adapter);
		}
		kref_get(&adapter->ref);
	}

	/* initialize request counter */
	BUG_ON(!zfcp_reqlist_isempty(adapter->req_list));
	adapter->req_no = 0;

	zfcp_ccw_activate(cdev, 0, "ccsonl1");

	/*
	 * We want to scan ports here, always, with some random delay and
	 * without rate limit - basically what zfcp_ccw_activate() has
	 * achieved for us. Not quite! That port scan depended on
	 * !no_auto_port_rescan. So let's cover the no_auto_port_rescan
	 * case here to make sure a port scan is done unconditionally.
	 * Since zfcp_ccw_activate() has waited the desired random time,
	 * we can immediately schedule and flush a port scan for the
	 * remaining cases.
	 */
	zfcp_fc_inverse_conditional_port_scan(adapter);
	flush_delayed_work(&adapter->scan_work);
	zfcp_ccw_adapter_put(adapter);
	return 0;
}