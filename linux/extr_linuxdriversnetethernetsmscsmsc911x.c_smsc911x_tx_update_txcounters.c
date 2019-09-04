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
struct smsc911x_data {int dummy; } ;
struct TYPE_2__ {unsigned int tx_bytes; int tx_carrier_errors; scalar_t__ tx_aborted_errors; scalar_t__ collisions; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMSC_WARN (struct smsc911x_data*,int /*<<< orphan*/ ,char*) ; 
 unsigned int TX_STS_ES_ ; 
 unsigned int TX_STS_EXCESS_COL_ ; 
 unsigned int TX_STS_LATE_COL_ ; 
 unsigned int TX_STS_LOST_CARRIER_ ; 
 int /*<<< orphan*/  hw ; 
 struct smsc911x_data* netdev_priv (struct net_device*) ; 
 unsigned int smsc911x_tx_get_txstatus (struct smsc911x_data*) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static void smsc911x_tx_update_txcounters(struct net_device *dev)
{
	struct smsc911x_data *pdata = netdev_priv(dev);
	unsigned int tx_stat;

	while ((tx_stat = smsc911x_tx_get_txstatus(pdata)) != 0) {
		if (unlikely(tx_stat & 0x80000000)) {
			/* In this driver the packet tag is used as the packet
			 * length. Since a packet length can never reach the
			 * size of 0x8000, this bit is reserved. It is worth
			 * noting that the "reserved bit" in the warning above
			 * does not reference a hardware defined reserved bit
			 * but rather a driver defined one.
			 */
			SMSC_WARN(pdata, hw, "Packet tag reserved bit is high");
		} else {
			if (unlikely(tx_stat & TX_STS_ES_)) {
				dev->stats.tx_errors++;
			} else {
				dev->stats.tx_packets++;
				dev->stats.tx_bytes += (tx_stat >> 16);
			}
			if (unlikely(tx_stat & TX_STS_EXCESS_COL_)) {
				dev->stats.collisions += 16;
				dev->stats.tx_aborted_errors += 1;
			} else {
				dev->stats.collisions +=
				    ((tx_stat >> 3) & 0xF);
			}
			if (unlikely(tx_stat & TX_STS_LOST_CARRIER_))
				dev->stats.tx_carrier_errors += 1;
			if (unlikely(tx_stat & TX_STS_LATE_COL_)) {
				dev->stats.collisions++;
				dev->stats.tx_aborted_errors++;
			}
		}
	}
}