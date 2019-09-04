#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  operation_mode; } ;
struct iw_statistics {int /*<<< orphan*/  status; } ;
struct ks_wlan_private {scalar_t__ dev_state; int /*<<< orphan*/  net_dev; int /*<<< orphan*/  confirm_wait; TYPE_1__ reg; struct iw_statistics wstats; } ;
struct TYPE_5__ {scalar_t__ expires; } ;

/* Variables and functions */
 scalar_t__ DEVICE_STATE_READY ; 
 int EBUSY ; 
 int EPERM ; 
 int HZ ; 
 int /*<<< orphan*/  SME_PHY_INFO_REQUEST ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostif_sme_enqueue (struct ks_wlan_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  update_phyinfo ; 
 TYPE_2__ update_phyinfo_timer ; 
 int /*<<< orphan*/  wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
int ks_wlan_update_phy_information(struct ks_wlan_private *priv)
{
	struct iw_statistics *wstats = &priv->wstats;

	netdev_dbg(priv->net_dev, "in_interrupt = %ld\n", in_interrupt());

	if (priv->dev_state < DEVICE_STATE_READY)
		return -EBUSY;	/* not finished initialize */

	if (atomic_read(&update_phyinfo))
		return -EPERM;

	/* The status */
	wstats->status = priv->reg.operation_mode;	/* Operation mode */

	/* Signal quality and co. But where is the noise level ??? */
	hostif_sme_enqueue(priv, SME_PHY_INFO_REQUEST);

	/* interruptible_sleep_on_timeout(&priv->confirm_wait, HZ/2); */
	if (!wait_for_completion_interruptible_timeout
	    (&priv->confirm_wait, HZ / 2)) {
		netdev_dbg(priv->net_dev, "wait time out!!\n");
	}

	atomic_inc(&update_phyinfo);
	update_phyinfo_timer.expires = jiffies + HZ;	/* 1sec */
	add_timer(&update_phyinfo_timer);

	return 0;
}