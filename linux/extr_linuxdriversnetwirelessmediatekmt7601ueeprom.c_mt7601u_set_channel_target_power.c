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
struct mt7601u_dev {TYPE_1__* ee; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  chan_pwr; } ;

/* Variables and functions */
 size_t MT_EE_TX_TSSI_TARGET_POWER ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void mt7601u_set_channel_target_power(struct mt7601u_dev *dev,
					     u8 *eeprom, u8 max_pwr)
{
	u8 trgt_pwr = eeprom[MT_EE_TX_TSSI_TARGET_POWER];

	if (trgt_pwr > max_pwr || !trgt_pwr) {
		dev_warn(dev->dev, "Error: EEPROM trgt power invalid %hhx!\n",
			 trgt_pwr);
		trgt_pwr = 0x20;
	}

	memset(dev->ee->chan_pwr, trgt_pwr, sizeof(dev->ee->chan_pwr));
}