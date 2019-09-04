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
typedef  int /*<<< orphan*/  u16 ;
struct mt76x0_rxwi {int dummy; } ;
struct mt76x0_dev {int avg_rssi; int /*<<< orphan*/  bcn_phy_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_RXWI_RATE_PHY ; 

__attribute__((used)) static void
mt76x0_rx_monitor_beacon(struct mt76x0_dev *dev, struct mt76x0_rxwi *rxwi,
			  u16 rate, int rssi)
{
	dev->bcn_phy_mode = FIELD_GET(MT_RXWI_RATE_PHY, rate);
	dev->avg_rssi = ((dev->avg_rssi * 15) / 16 + (rssi << 8)) / 256;
}