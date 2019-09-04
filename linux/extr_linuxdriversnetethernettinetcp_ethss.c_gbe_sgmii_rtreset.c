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
struct gbe_slave {int /*<<< orphan*/  slave_num; } ;
struct gbe_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGMII_BASE (struct gbe_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ SLAVE_LINK_IS_XGMII (struct gbe_slave*) ; 
 int /*<<< orphan*/  netcp_sgmii_rtreset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gbe_sgmii_rtreset(struct gbe_priv *priv,
			      struct gbe_slave *slave, bool set)
{
	if (SLAVE_LINK_IS_XGMII(slave))
		return;

	netcp_sgmii_rtreset(SGMII_BASE(priv, slave->slave_num),
			    slave->slave_num, set);
}