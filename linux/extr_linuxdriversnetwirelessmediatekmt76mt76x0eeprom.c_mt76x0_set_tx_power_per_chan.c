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
typedef  int u8 ;
struct mt76x0_dev {TYPE_1__* ee; } ;
struct TYPE_2__ {int* tx_pwr_per_chan; } ;

/* Variables and functions */
 int MT_EE_TX_POWER_OFFSET_2GHZ ; 
 int MT_EE_TX_POWER_OFFSET_5GHZ ; 

__attribute__((used)) static void
mt76x0_set_tx_power_per_chan(struct mt76x0_dev *dev, u8 *eeprom)
{
	int i;
	u8 tx_pwr;

	for (i = 0; i < 14; i++) {
		tx_pwr = eeprom[MT_EE_TX_POWER_OFFSET_2GHZ + i];
		if (tx_pwr <= 0x3f && tx_pwr > 0)
			dev->ee->tx_pwr_per_chan[i] = tx_pwr;
		else
			dev->ee->tx_pwr_per_chan[i] = 5;
	}

	for (i = 0; i < 40; i++) {
		tx_pwr = eeprom[MT_EE_TX_POWER_OFFSET_5GHZ + i];
		if (tx_pwr <= 0x3f && tx_pwr > 0)
			dev->ee->tx_pwr_per_chan[14 + i] = tx_pwr;
		else
			dev->ee->tx_pwr_per_chan[14 + i] = 5;
	}

	dev->ee->tx_pwr_per_chan[54] = dev->ee->tx_pwr_per_chan[22];
	dev->ee->tx_pwr_per_chan[55] = dev->ee->tx_pwr_per_chan[28];
	dev->ee->tx_pwr_per_chan[56] = dev->ee->tx_pwr_per_chan[34];
	dev->ee->tx_pwr_per_chan[57] = dev->ee->tx_pwr_per_chan[44];
}