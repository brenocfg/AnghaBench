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
struct switch_port_stats {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; } ;
struct switch_dev {int dummy; } ;
struct ar7240sw {int /*<<< orphan*/  stats_lock; TYPE_1__* port_stats; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_byte; int /*<<< orphan*/  rx_good_byte; } ;

/* Variables and functions */
 int AR7240_NUM_PORTS ; 
 int EINVAL ; 
 int /*<<< orphan*/  ar7240sw_capture_stats (struct ar7240sw*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 struct ar7240sw* sw_to_ar7240 (struct switch_dev*) ; 

__attribute__((used)) static int
ar7240_get_port_stats(struct switch_dev *dev, int port,
		      struct switch_port_stats *stats)
{
	struct ar7240sw *as = sw_to_ar7240(dev);

	if (port >= AR7240_NUM_PORTS)
		return -EINVAL;

	ar7240sw_capture_stats(as);

	read_lock(&as->stats_lock);
	stats->rx_bytes = as->port_stats[port].rx_good_byte;
	stats->tx_bytes = as->port_stats[port].tx_byte;
	read_unlock(&as->stats_lock);

	return 0;
}