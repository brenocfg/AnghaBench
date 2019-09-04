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
struct TYPE_2__ {int lna_gain_2ghz; int* lna_gain_5ghz; } ;

/* Variables and functions */
 size_t MT_EE_LNA_GAIN_2GHZ ; 
 size_t MT_EE_LNA_GAIN_5GHZ_0 ; 
 size_t MT_EE_LNA_GAIN_5GHZ_1 ; 
 size_t MT_EE_LNA_GAIN_5GHZ_2 ; 

__attribute__((used)) static void
mt76x0_set_lna_gain(struct mt76x0_dev *dev, u8 *eeprom)
{
	u8 gain;

	dev->ee->lna_gain_2ghz = eeprom[MT_EE_LNA_GAIN_2GHZ];
	dev->ee->lna_gain_5ghz[0] = eeprom[MT_EE_LNA_GAIN_5GHZ_0];

	gain = eeprom[MT_EE_LNA_GAIN_5GHZ_1];
	if (gain == 0xff || gain == 0)
		dev->ee->lna_gain_5ghz[1] = dev->ee->lna_gain_5ghz[0];
	else
		dev->ee->lna_gain_5ghz[1] = gain;

	gain = eeprom[MT_EE_LNA_GAIN_5GHZ_2];
	if (gain == 0xff || gain == 0)
		dev->ee->lna_gain_5ghz[2] = dev->ee->lna_gain_5ghz[0];
	else
		dev->ee->lna_gain_5ghz[2] = gain;
}