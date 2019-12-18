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
typedef  int /*<<< orphan*/  u32 ;
struct tc_mqprio_qopt {int num_tc; int* prio_tc_map; unsigned int* offset; unsigned int* count; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int num_tx_queues; unsigned int real_num_tx_queues; scalar_t__ num_tc; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int TC_BITMASK ; 
 int TC_MAX_QUEUE ; 
 scalar_t__ TXTIME_ASSIST_IS_ENABLED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int taprio_parse_mqprio_opt(struct net_device *dev,
				   struct tc_mqprio_qopt *qopt,
				   struct netlink_ext_ack *extack,
				   u32 taprio_flags)
{
	int i, j;

	if (!qopt && !dev->num_tc) {
		NL_SET_ERR_MSG(extack, "'mqprio' configuration is necessary");
		return -EINVAL;
	}

	/* If num_tc is already set, it means that the user already
	 * configured the mqprio part
	 */
	if (dev->num_tc)
		return 0;

	/* Verify num_tc is not out of max range */
	if (qopt->num_tc > TC_MAX_QUEUE) {
		NL_SET_ERR_MSG(extack, "Number of traffic classes is outside valid range");
		return -EINVAL;
	}

	/* taprio imposes that traffic classes map 1:n to tx queues */
	if (qopt->num_tc > dev->num_tx_queues) {
		NL_SET_ERR_MSG(extack, "Number of traffic classes is greater than number of HW queues");
		return -EINVAL;
	}

	/* Verify priority mapping uses valid tcs */
	for (i = 0; i < TC_BITMASK + 1; i++) {
		if (qopt->prio_tc_map[i] >= qopt->num_tc) {
			NL_SET_ERR_MSG(extack, "Invalid traffic class in priority to traffic class mapping");
			return -EINVAL;
		}
	}

	for (i = 0; i < qopt->num_tc; i++) {
		unsigned int last = qopt->offset[i] + qopt->count[i];

		/* Verify the queue count is in tx range being equal to the
		 * real_num_tx_queues indicates the last queue is in use.
		 */
		if (qopt->offset[i] >= dev->num_tx_queues ||
		    !qopt->count[i] ||
		    last > dev->real_num_tx_queues) {
			NL_SET_ERR_MSG(extack, "Invalid queue in traffic class to queue mapping");
			return -EINVAL;
		}

		if (TXTIME_ASSIST_IS_ENABLED(taprio_flags))
			continue;

		/* Verify that the offset and counts do not overlap */
		for (j = i + 1; j < qopt->num_tc; j++) {
			if (last > qopt->offset[j]) {
				NL_SET_ERR_MSG(extack, "Detected overlap in the traffic class to queue mapping");
				return -EINVAL;
			}
		}
	}

	return 0;
}