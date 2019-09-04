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
struct tc_mqprio_qopt {int num_tc; int* prio_tc_map; scalar_t__ hw; unsigned int* offset; unsigned int* count; } ;
struct net_device {unsigned int real_num_tx_queues; TYPE_1__* netdev_ops; } ;
struct TYPE_2__ {scalar_t__ ndo_setup_tc; } ;

/* Variables and functions */
 int EINVAL ; 
 int TC_BITMASK ; 
 int TC_MAX_QUEUE ; 
 scalar_t__ TC_MQPRIO_HW_OFFLOAD_MAX ; 

__attribute__((used)) static int mqprio_parse_opt(struct net_device *dev, struct tc_mqprio_qopt *qopt)
{
	int i, j;

	/* Verify num_tc is not out of max range */
	if (qopt->num_tc > TC_MAX_QUEUE)
		return -EINVAL;

	/* Verify priority mapping uses valid tcs */
	for (i = 0; i < TC_BITMASK + 1; i++) {
		if (qopt->prio_tc_map[i] >= qopt->num_tc)
			return -EINVAL;
	}

	/* Limit qopt->hw to maximum supported offload value.  Drivers have
	 * the option of overriding this later if they don't support the a
	 * given offload type.
	 */
	if (qopt->hw > TC_MQPRIO_HW_OFFLOAD_MAX)
		qopt->hw = TC_MQPRIO_HW_OFFLOAD_MAX;

	/* If hardware offload is requested we will leave it to the device
	 * to either populate the queue counts itself or to validate the
	 * provided queue counts.  If ndo_setup_tc is not present then
	 * hardware doesn't support offload and we should return an error.
	 */
	if (qopt->hw)
		return dev->netdev_ops->ndo_setup_tc ? 0 : -EINVAL;

	for (i = 0; i < qopt->num_tc; i++) {
		unsigned int last = qopt->offset[i] + qopt->count[i];

		/* Verify the queue count is in tx range being equal to the
		 * real_num_tx_queues indicates the last queue is in use.
		 */
		if (qopt->offset[i] >= dev->real_num_tx_queues ||
		    !qopt->count[i] ||
		    last > dev->real_num_tx_queues)
			return -EINVAL;

		/* Verify that the offset and counts do not overlap */
		for (j = i + 1; j < qopt->num_tc; j++) {
			if (last > qopt->offset[j])
				return -EINVAL;
		}
	}

	return 0;
}