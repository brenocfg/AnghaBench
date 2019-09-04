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
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct cpsw_priv {int /*<<< orphan*/  dev; struct cpsw_common* cpsw; } ;
struct TYPE_3__ {scalar_t__ default_vlan; int slaves; scalar_t__ dual_emac; } ;
struct cpsw_common {int /*<<< orphan*/  dev; TYPE_2__* slaves; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {scalar_t__ port_vlan; } ;

/* Variables and functions */
 int EINVAL ; 
 int cpsw_add_vlan_ale_entry (struct cpsw_priv*,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpsw_ndo_vlan_rx_add_vid(struct net_device *ndev,
				    __be16 proto, u16 vid)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	struct cpsw_common *cpsw = priv->cpsw;
	int ret;

	if (vid == cpsw->data.default_vlan)
		return 0;

	ret = pm_runtime_get_sync(cpsw->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(cpsw->dev);
		return ret;
	}

	if (cpsw->data.dual_emac) {
		/* In dual EMAC, reserved VLAN id should not be used for
		 * creating VLAN interfaces as this can break the dual
		 * EMAC port separation
		 */
		int i;

		for (i = 0; i < cpsw->data.slaves; i++) {
			if (vid == cpsw->slaves[i].port_vlan) {
				ret = -EINVAL;
				goto err;
			}
		}
	}

	dev_info(priv->dev, "Adding vlanid %d to vlan filter\n", vid);
	ret = cpsw_add_vlan_ale_entry(priv, vid);
err:
	pm_runtime_put(cpsw->dev);
	return ret;
}