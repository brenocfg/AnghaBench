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
struct wireless_dev {int iftype; int* address; struct wiphy* wiphy; } ;
struct wiphy {int dummy; } ;
struct wil6210_vif {int mid; } ;
struct wil6210_priv {TYPE_1__* wiphy; struct wireless_dev* p2p_wdev; struct net_device* main_ndev; } ;
struct vif_params {int* macaddr; } ;
struct net_device {int* perm_addr; int* dev_addr; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_2__ {int /*<<< orphan*/  n_iface_combinations; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct wireless_dev* ERR_CAST (struct wil6210_vif*) ; 
 struct wireless_dev* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct wil6210_vif*) ; 
 int NL80211_IFTYPE_P2P_DEVICE ; 
 int /*<<< orphan*/  ether_addr_copy (int*,int*) ; 
 scalar_t__ is_valid_ether_addr (int*) ; 
 struct wireless_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct net_device* vif_to_ndev (struct wil6210_vif*) ; 
 struct wireless_dev* vif_to_wdev (struct wil6210_vif*) ; 
 int wil_cfg80211_validate_add_iface (struct wil6210_priv*,int) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,int) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,...) ; 
 int /*<<< orphan*/  wil_info (struct wil6210_priv*,char*,int,int,int*) ; 
 int wil_vif_add (struct wil6210_priv*,struct wil6210_vif*) ; 
 struct wil6210_vif* wil_vif_alloc (struct wil6210_priv*,char const*,unsigned char,int) ; 
 int /*<<< orphan*/  wil_vif_free (struct wil6210_vif*) ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 

__attribute__((used)) static struct wireless_dev *
wil_cfg80211_add_iface(struct wiphy *wiphy, const char *name,
		       unsigned char name_assign_type,
		       enum nl80211_iftype type,
		       struct vif_params *params)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	struct net_device *ndev_main = wil->main_ndev, *ndev;
	struct wil6210_vif *vif;
	struct wireless_dev *p2p_wdev, *wdev;
	int rc;

	wil_dbg_misc(wil, "add_iface, type %d\n", type);

	/* P2P device is not a real virtual interface, it is a management-only
	 * interface that shares the main interface.
	 * Skip concurrency checks here.
	 */
	if (type == NL80211_IFTYPE_P2P_DEVICE) {
		if (wil->p2p_wdev) {
			wil_err(wil, "P2P_DEVICE interface already created\n");
			return ERR_PTR(-EINVAL);
		}

		p2p_wdev = kzalloc(sizeof(*p2p_wdev), GFP_KERNEL);
		if (!p2p_wdev)
			return ERR_PTR(-ENOMEM);

		p2p_wdev->iftype = type;
		p2p_wdev->wiphy = wiphy;
		/* use our primary ethernet address */
		ether_addr_copy(p2p_wdev->address, ndev_main->perm_addr);

		wil->p2p_wdev = p2p_wdev;

		return p2p_wdev;
	}

	if (!wil->wiphy->n_iface_combinations) {
		wil_err(wil, "virtual interfaces not supported\n");
		return ERR_PTR(-EINVAL);
	}

	rc = wil_cfg80211_validate_add_iface(wil, type);
	if (rc) {
		wil_err(wil, "iface validation failed, err=%d\n", rc);
		return ERR_PTR(rc);
	}

	vif = wil_vif_alloc(wil, name, name_assign_type, type);
	if (IS_ERR(vif))
		return ERR_CAST(vif);

	ndev = vif_to_ndev(vif);
	ether_addr_copy(ndev->perm_addr, ndev_main->perm_addr);
	if (is_valid_ether_addr(params->macaddr)) {
		ether_addr_copy(ndev->dev_addr, params->macaddr);
	} else {
		ether_addr_copy(ndev->dev_addr, ndev_main->perm_addr);
		ndev->dev_addr[0] = (ndev->dev_addr[0] ^ (1 << vif->mid)) |
			0x2; /* locally administered */
	}
	wdev = vif_to_wdev(vif);
	ether_addr_copy(wdev->address, ndev->dev_addr);

	rc = wil_vif_add(wil, vif);
	if (rc)
		goto out;

	wil_info(wil, "added VIF, mid %d iftype %d MAC %pM\n",
		 vif->mid, type, wdev->address);
	return wdev;
out:
	wil_vif_free(vif);
	return ERR_PTR(rc);
}