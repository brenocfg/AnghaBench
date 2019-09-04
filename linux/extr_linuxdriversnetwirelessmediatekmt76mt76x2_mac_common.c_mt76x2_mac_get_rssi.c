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
struct mt76x2_rx_freq_cal {scalar_t__ lna_gain; scalar_t__* rssi_offset; } ;
struct TYPE_2__ {struct mt76x2_rx_freq_cal rx; } ;
struct mt76x2_dev {TYPE_1__ cal; } ;
typedef  int s8 ;

/* Variables and functions */

int mt76x2_mac_get_rssi(struct mt76x2_dev *dev, s8 rssi, int chain)
{
	struct mt76x2_rx_freq_cal *cal = &dev->cal.rx;

	rssi += cal->rssi_offset[chain];
	rssi -= cal->lna_gain;

	return rssi;
}