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
struct vmxnet3_adapter {int num_rx_queues; int /*<<< orphan*/  rxdataring_enabled; TYPE_1__* netdev; int /*<<< orphan*/ * rx_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_VERSION_GE_3 (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int vmxnet3_rq_create (int /*<<< orphan*/ *,struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_rq_destroy_all (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_rq_destroy_all_rxdataring (struct vmxnet3_adapter*) ; 

__attribute__((used)) static int
vmxnet3_rq_create_all(struct vmxnet3_adapter *adapter)
{
	int i, err = 0;

	adapter->rxdataring_enabled = VMXNET3_VERSION_GE_3(adapter);

	for (i = 0; i < adapter->num_rx_queues; i++) {
		err = vmxnet3_rq_create(&adapter->rx_queue[i], adapter);
		if (unlikely(err)) {
			dev_err(&adapter->netdev->dev,
				"%s: failed to create rx queue%i\n",
				adapter->netdev->name, i);
			goto err_out;
		}
	}

	if (!adapter->rxdataring_enabled)
		vmxnet3_rq_destroy_all_rxdataring(adapter);

	return err;
err_out:
	vmxnet3_rq_destroy_all(adapter);
	return err;

}