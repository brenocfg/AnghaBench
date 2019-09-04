#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mt76x0_rxwi {int* rssi; } ;
struct TYPE_8__ {TYPE_2__* chan; } ;
struct TYPE_7__ {TYPE_4__ chandef; } ;
struct mt76x0_dev {TYPE_1__* ee; TYPE_3__ mt76; } ;
typedef  int s8 ;
struct TYPE_6__ {scalar_t__ band; } ;
struct TYPE_5__ {int lna_gain_2ghz; int* rssi_offset_2ghz; int* lna_gain_5ghz; int* rssi_offset_5ghz; } ;

/* Variables and functions */
 scalar_t__ NL80211_BAND_2GHZ ; 

int mt76x0_phy_get_rssi(struct mt76x0_dev *dev, struct mt76x0_rxwi *rxwi)
{
	s8 lna_gain, rssi_offset;
	int val;

	if (dev->mt76.chandef.chan->band == NL80211_BAND_2GHZ) {
		lna_gain = dev->ee->lna_gain_2ghz;
		rssi_offset = dev->ee->rssi_offset_2ghz[0];
	} else {
		lna_gain = dev->ee->lna_gain_5ghz[0];
		rssi_offset = dev->ee->rssi_offset_5ghz[0];
	}

	val = rxwi->rssi[0] + rssi_offset - lna_gain;

	return val;
}