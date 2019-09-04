#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  work; int /*<<< orphan*/  lock; scalar_t__ direct_probe; } ;
struct cw1200_common {TYPE_2__ scan; TYPE_1__* hw; int /*<<< orphan*/  clear_recent_scan_work; int /*<<< orphan*/  workqueue; } ;
struct TYPE_3__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  cw1200_scan_restart_delayed (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_scan_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wsm_unlock_tx (struct cw1200_common*) ; 

__attribute__((used)) static void cw1200_scan_complete(struct cw1200_common *priv)
{
	queue_delayed_work(priv->workqueue, &priv->clear_recent_scan_work, HZ);
	if (priv->scan.direct_probe) {
		wiphy_dbg(priv->hw->wiphy, "[SCAN] Direct probe complete.\n");
		cw1200_scan_restart_delayed(priv);
		priv->scan.direct_probe = 0;
		up(&priv->scan.lock);
		wsm_unlock_tx(priv);
	} else {
		cw1200_scan_work(&priv->scan.work);
	}
}