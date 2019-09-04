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
typedef  int u32 ;
struct wilc_vif {struct wilc* wilc; } ;
struct wilc {int quit; TYPE_1__* hif_func; struct txq_entry_t* tx_buffer; struct txq_entry_t* rx_buffer; } ;
struct txq_entry_t {int /*<<< orphan*/  priv; int /*<<< orphan*/  (* tx_complete_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct rxq_entry_t {int /*<<< orphan*/  priv; int /*<<< orphan*/  (* tx_complete_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int (* hif_read_reg ) (struct wilc*,int /*<<< orphan*/ ,int*) ;int (* hif_write_reg ) (struct wilc*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* hif_deinit ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ABORT_INT ; 
 int /*<<< orphan*/  ACQUIRE_AND_WAKEUP ; 
 int /*<<< orphan*/  RELEASE_ALLOW_SLEEP ; 
 int /*<<< orphan*/  WILC_GP_REG_0 ; 
 int /*<<< orphan*/  acquire_bus (struct wilc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct txq_entry_t*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  release_bus (struct wilc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct wilc*,int /*<<< orphan*/ ,int*) ; 
 int stub3 (struct wilc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 
 struct txq_entry_t* wilc_wlan_rxq_remove (struct wilc*) ; 
 struct txq_entry_t* wilc_wlan_txq_remove_from_head (struct net_device*) ; 

void wilc_wlan_cleanup(struct net_device *dev)
{
	struct txq_entry_t *tqe;
	struct rxq_entry_t *rqe;
	u32 reg = 0;
	int ret;
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wilc = vif->wilc;

	wilc->quit = 1;
	do {
		tqe = wilc_wlan_txq_remove_from_head(dev);
		if (!tqe)
			break;
		if (tqe->tx_complete_func)
			tqe->tx_complete_func(tqe->priv, 0);
		kfree(tqe);
	} while (1);

	do {
		rqe = wilc_wlan_rxq_remove(wilc);
		if (!rqe)
			break;
		kfree(rqe);
	} while (1);

	kfree(wilc->rx_buffer);
	wilc->rx_buffer = NULL;
	kfree(wilc->tx_buffer);
	wilc->tx_buffer = NULL;

	acquire_bus(wilc, ACQUIRE_AND_WAKEUP);

	ret = wilc->hif_func->hif_read_reg(wilc, WILC_GP_REG_0, &reg);
	if (!ret)
		release_bus(wilc, RELEASE_ALLOW_SLEEP);

	ret = wilc->hif_func->hif_write_reg(wilc, WILC_GP_REG_0,
					(reg | ABORT_INT));
	if (!ret)
		release_bus(wilc, RELEASE_ALLOW_SLEEP);

	release_bus(wilc, RELEASE_ALLOW_SLEEP);
	wilc->hif_func->hif_deinit(NULL);
}