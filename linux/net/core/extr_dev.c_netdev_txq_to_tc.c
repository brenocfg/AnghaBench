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
struct netdev_tc_txq {unsigned int offset; unsigned int count; } ;
struct net_device {struct netdev_tc_txq* tc_to_txq; scalar_t__ num_tc; } ;

/* Variables and functions */
 int TC_MAX_QUEUE ; 

int netdev_txq_to_tc(struct net_device *dev, unsigned int txq)
{
	if (dev->num_tc) {
		struct netdev_tc_txq *tc = &dev->tc_to_txq[0];
		int i;

		/* walk through the TCs and see if it falls into any of them */
		for (i = 0; i < TC_MAX_QUEUE; i++, tc++) {
			if ((txq - tc->offset) < tc->count)
				return i;
		}

		/* didn't find it, just return -1 to indicate no match */
		return -1;
	}

	return 0;
}