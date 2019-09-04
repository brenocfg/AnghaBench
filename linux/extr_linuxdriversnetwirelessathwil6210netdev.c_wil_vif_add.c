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
struct wireless_dev {int /*<<< orphan*/  iftype; } ;
struct wil6210_vif {size_t mid; } ;
struct wil6210_priv {struct wil6210_vif** vifs; } ;
struct net_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EEXIST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int register_netdevice (struct net_device*) ; 
 struct net_device* vif_to_ndev (struct wil6210_vif*) ; 
 struct wireless_dev* vif_to_wdev (struct wil6210_vif*) ; 
 int wil_has_active_ifaces (struct wil6210_priv*,int,int) ; 
 int wmi_port_allocate (struct wil6210_priv*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmi_port_delete (struct wil6210_priv*,scalar_t__) ; 

int wil_vif_add(struct wil6210_priv *wil, struct wil6210_vif *vif)
{
	struct net_device *ndev = vif_to_ndev(vif);
	struct wireless_dev *wdev = vif_to_wdev(vif);
	bool any_active = wil_has_active_ifaces(wil, true, false);
	int rc;

	ASSERT_RTNL();

	if (wil->vifs[vif->mid]) {
		dev_err(&ndev->dev, "VIF with mid %d already in use\n",
			vif->mid);
		return -EEXIST;
	}
	if (any_active && vif->mid != 0) {
		rc = wmi_port_allocate(wil, vif->mid, ndev->dev_addr,
				       wdev->iftype);
		if (rc)
			return rc;
	}
	rc = register_netdevice(ndev);
	if (rc < 0) {
		dev_err(&ndev->dev, "Failed to register netdev: %d\n", rc);
		if (any_active && vif->mid != 0)
			wmi_port_delete(wil, vif->mid);
		return rc;
	}

	wil->vifs[vif->mid] = vif;
	return 0;
}