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
struct TYPE_2__ {int /*<<< orphan*/  is_dsp_busy; int /*<<< orphan*/  tx_data_copy; int /*<<< orphan*/  tx_msg; } ;
struct sst_generic_ipc {TYPE_1__ ops; int /*<<< orphan*/  rx_data_max_size; int /*<<< orphan*/  tx_data_max_size; struct device* dev; int /*<<< orphan*/  dsp; } ;
struct skl_dev {int /*<<< orphan*/  dsp; struct sst_generic_ipc ipc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKL_ADSP_W0_UP_SZ ; 
 int /*<<< orphan*/  SKL_ADSP_W1_SZ ; 
 int /*<<< orphan*/  skl_ipc_is_dsp_busy ; 
 int /*<<< orphan*/  skl_ipc_tx_data_copy ; 
 int /*<<< orphan*/  skl_ipc_tx_msg ; 
 int sst_ipc_init (struct sst_generic_ipc*) ; 

int skl_ipc_init(struct device *dev, struct skl_dev *skl)
{
	struct sst_generic_ipc *ipc;
	int err;

	ipc = &skl->ipc;
	ipc->dsp = skl->dsp;
	ipc->dev = dev;

	ipc->tx_data_max_size = SKL_ADSP_W1_SZ;
	ipc->rx_data_max_size = SKL_ADSP_W0_UP_SZ;

	err = sst_ipc_init(ipc);
	if (err)
		return err;

	ipc->ops.tx_msg = skl_ipc_tx_msg;
	ipc->ops.tx_data_copy = skl_ipc_tx_data_copy;
	ipc->ops.is_dsp_busy = skl_ipc_is_dsp_busy;

	return 0;
}