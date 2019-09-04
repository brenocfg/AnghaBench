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
struct iwl_trans_rxq_dma_data {scalar_t__ fr_bd_wid; int /*<<< orphan*/  ur_bd_cb; int /*<<< orphan*/  urbd_stts_wrptr; int /*<<< orphan*/  fr_bd_cb; } ;
struct iwl_trans_pcie {TYPE_1__* rxq; } ;
struct iwl_trans {int num_rx_queues; } ;
struct TYPE_2__ {int /*<<< orphan*/  used_bd_dma; int /*<<< orphan*/  rb_stts_dma; int /*<<< orphan*/  bd_dma; } ;

/* Variables and functions */
 int EINVAL ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 

__attribute__((used)) static int iwl_trans_pcie_rxq_dma_data(struct iwl_trans *trans, int queue,
				       struct iwl_trans_rxq_dma_data *data)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	if (queue >= trans->num_rx_queues || !trans_pcie->rxq)
		return -EINVAL;

	data->fr_bd_cb = trans_pcie->rxq[queue].bd_dma;
	data->urbd_stts_wrptr = trans_pcie->rxq[queue].rb_stts_dma;
	data->ur_bd_cb = trans_pcie->rxq[queue].used_bd_dma;
	data->fr_bd_wid = 0;

	return 0;
}