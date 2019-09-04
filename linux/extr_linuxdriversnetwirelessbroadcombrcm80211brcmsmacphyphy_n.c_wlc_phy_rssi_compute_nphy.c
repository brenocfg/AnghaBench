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
struct d11rxhdr {int PhyRxStatus_1; int PhyRxStatus_0; int PhyRxStatus_2; } ;
struct brcms_phy {TYPE_1__* sh; } ;
typedef  int s16 ;
struct TYPE_2__ {scalar_t__ rssi_mode; } ;

/* Variables and functions */
 int PRXS1_nphy_PWR0_MASK ; 
 int PRXS1_nphy_PWR1_MASK ; 
 scalar_t__ RSSI_ANT_MERGE_AVG ; 
 scalar_t__ RSSI_ANT_MERGE_MAX ; 
 scalar_t__ RSSI_ANT_MERGE_MIN ; 

int
wlc_phy_rssi_compute_nphy(struct brcms_phy *pi, struct d11rxhdr *rxh)
{
	s16 rxpwr, rxpwr0, rxpwr1;
	s16 phyRx0_l, phyRx2_l;

	rxpwr = 0;
	rxpwr0 = rxh->PhyRxStatus_1 & PRXS1_nphy_PWR0_MASK;
	rxpwr1 = (rxh->PhyRxStatus_1 & PRXS1_nphy_PWR1_MASK) >> 8;

	if (rxpwr0 > 127)
		rxpwr0 -= 256;
	if (rxpwr1 > 127)
		rxpwr1 -= 256;

	phyRx0_l = rxh->PhyRxStatus_0 & 0x00ff;
	phyRx2_l = rxh->PhyRxStatus_2 & 0x00ff;
	if (phyRx2_l > 127)
		phyRx2_l -= 256;

	if (((rxpwr0 == 16) || (rxpwr0 == 32))) {
		rxpwr0 = rxpwr1;
		rxpwr1 = phyRx2_l;
	}

	if (pi->sh->rssi_mode == RSSI_ANT_MERGE_MAX)
		rxpwr = (rxpwr0 > rxpwr1) ? rxpwr0 : rxpwr1;
	else if (pi->sh->rssi_mode == RSSI_ANT_MERGE_MIN)
		rxpwr = (rxpwr0 < rxpwr1) ? rxpwr0 : rxpwr1;
	else if (pi->sh->rssi_mode == RSSI_ANT_MERGE_AVG)
		rxpwr = (rxpwr0 + rxpwr1) >> 1;

	return rxpwr;
}