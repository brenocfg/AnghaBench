#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct mt76x0_dev {TYPE_2__ mt76; TYPE_1__* ee; } ;
typedef  int s8 ;
struct TYPE_3__ {int* rssi_offset_2ghz; int* rssi_offset_5ghz; } ;

/* Variables and functions */
 int MT_EE_RSSI_OFFSET ; 
 int MT_EE_RSSI_OFFSET_5GHZ ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
mt76x0_set_rssi_offset(struct mt76x0_dev *dev, u8 *eeprom)
{
	int i;
	s8 *rssi_offset = dev->ee->rssi_offset_2ghz;

	for (i = 0; i < 2; i++) {
		rssi_offset[i] = eeprom[MT_EE_RSSI_OFFSET + i];

		if (rssi_offset[i] < -10 || rssi_offset[i] > 10) {
			dev_warn(dev->mt76.dev,
				 "Warning: EEPROM RSSI is invalid %02hhx\n",
				 rssi_offset[i]);
			rssi_offset[i] = 0;
		}
	}

	rssi_offset = dev->ee->rssi_offset_5ghz;

	for (i = 0; i < 3; i++) {
		rssi_offset[i] = eeprom[MT_EE_RSSI_OFFSET_5GHZ + i];

		if (rssi_offset[i] < -10 || rssi_offset[i] > 10) {
			dev_warn(dev->mt76.dev,
				 "Warning: EEPROM RSSI is invalid %02hhx\n",
				 rssi_offset[i]);
			rssi_offset[i] = 0;
		}
	}
}