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
typedef  int /*<<< orphan*/  u8 ;
struct cpsw_slave {int /*<<< orphan*/  port_vlan; int /*<<< orphan*/  slave_num; } ;
struct cpsw_priv {int emac_port; struct cpsw_common* cpsw; } ;
struct TYPE_2__ {scalar_t__ dual_emac; } ;
struct cpsw_common {int /*<<< orphan*/  ale; struct cpsw_slave* slaves; TYPE_1__ data; } ;

/* Variables and functions */
 int ALE_ALL_PORTS ; 
 int ALE_PORT_HOST ; 
 int /*<<< orphan*/  ALE_VLAN ; 
 int /*<<< orphan*/  cpsw_ale_add_mcast (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cpsw_get_slave_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpsw_add_mcast(struct cpsw_priv *priv, u8 *addr)
{
	struct cpsw_common *cpsw = priv->cpsw;

	if (cpsw->data.dual_emac) {
		struct cpsw_slave *slave = cpsw->slaves + priv->emac_port;
		int slave_port = cpsw_get_slave_port(slave->slave_num);

		cpsw_ale_add_mcast(cpsw->ale, addr,
				   1 << slave_port | ALE_PORT_HOST,
				   ALE_VLAN, slave->port_vlan, 0);
		return;
	}

	cpsw_ale_add_mcast(cpsw->ale, addr, ALE_ALL_PORTS, 0, 0, 0);
}