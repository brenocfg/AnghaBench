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
typedef  int /*<<< orphan*/  wilc_tx_complete_func_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wilc_vif {struct wilc* wilc; } ;
struct wilc {scalar_t__ quit; } ;
struct txq_entry_t {int /*<<< orphan*/  tcp_pending_ack_idx; void* priv; int /*<<< orphan*/  tx_complete_func; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  type; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NOT_TCP_ACK ; 
 int /*<<< orphan*/  WILC_MGMT_PKT ; 
 struct txq_entry_t* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wilc_wlan_txq_add_to_tail (struct net_device*,struct txq_entry_t*) ; 

int wilc_wlan_txq_add_mgmt_pkt(struct net_device *dev, void *priv, u8 *buffer,
			       u32 buffer_size, wilc_tx_complete_func_t func)
{
	struct txq_entry_t *tqe;
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wilc;

	wilc = vif->wilc;

	if (wilc->quit)
		return 0;

	tqe = kmalloc(sizeof(*tqe), GFP_KERNEL);

	if (!tqe)
		return 0;
	tqe->type = WILC_MGMT_PKT;
	tqe->buffer = buffer;
	tqe->buffer_size = buffer_size;
	tqe->tx_complete_func = func;
	tqe->priv = priv;
	tqe->tcp_pending_ack_idx = NOT_TCP_ACK;
	wilc_wlan_txq_add_to_tail(dev, tqe);
	return 1;
}