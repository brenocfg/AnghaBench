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
typedef  int u32 ;
struct cpsw_slave {int dummy; } ;
struct cpsw_priv {int /*<<< orphan*/  ndev; int /*<<< orphan*/  mqprio_hw; struct cpsw_common* cpsw; } ;
struct cpsw_common {scalar_t__ version; } ;

/* Variables and functions */
 int CPSW1_TX_PRI_MAP ; 
 int CPSW2_TX_PRI_MAP ; 
 int CPSW_FIFO_SHAPERS_NUM ; 
 scalar_t__ CPSW_VERSION_1 ; 
 int netdev_get_prio_tc_map (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  slave_write (struct cpsw_slave*,int,int) ; 

__attribute__((used)) static void cpsw_mqprio_resume(struct cpsw_slave *slave, struct cpsw_priv *priv)
{
	struct cpsw_common *cpsw = priv->cpsw;
	u32 tx_prio_map = 0;
	int i, tc, fifo;
	u32 tx_prio_rg;

	if (!priv->mqprio_hw)
		return;

	for (i = 0; i < 8; i++) {
		tc = netdev_get_prio_tc_map(priv->ndev, i);
		fifo = CPSW_FIFO_SHAPERS_NUM - tc;
		tx_prio_map |= fifo << (4 * i);
	}

	tx_prio_rg = cpsw->version == CPSW_VERSION_1 ?
		     CPSW1_TX_PRI_MAP : CPSW2_TX_PRI_MAP;

	slave_write(slave, tx_prio_map, tx_prio_rg);
}