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
struct TYPE_2__ {int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 unsigned int RX_STS_CRC_ERR_ ; 
 unsigned int RX_STS_ES_ ; 
 unsigned int RX_STS_FRAME_TYPE_ ; 
 unsigned int RX_STS_LENGTH_ERR_ ; 
 unsigned int RX_STS_MCAST_ ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
smsc911x_rx_counterrors(struct net_device *dev, unsigned int rxstat)
{
	int crc_err = 0;

	if (unlikely(rxstat & RX_STS_ES_)) {
		dev->stats.rx_errors++;
		if (unlikely(rxstat & RX_STS_CRC_ERR_)) {
			dev->stats.rx_crc_errors++;
			crc_err = 1;
		}
	}
	if (likely(!crc_err)) {
		if (unlikely((rxstat & RX_STS_FRAME_TYPE_) &&
			     (rxstat & RX_STS_LENGTH_ERR_)))
			dev->stats.rx_length_errors++;
		if (rxstat & RX_STS_MCAST_)
			dev->stats.multicast++;
	}
}