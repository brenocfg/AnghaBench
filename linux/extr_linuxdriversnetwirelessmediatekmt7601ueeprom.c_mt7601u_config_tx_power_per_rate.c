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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct mt7601u_dev {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int MT_EE_TX_POWER_BYRATE (int) ; 
 size_t MT_EE_TX_POWER_DELTA_BW40 ; 
 scalar_t__ MT_TX_PWR_CFG_0 ; 
 int /*<<< orphan*/  get_delta (int /*<<< orphan*/ ) ; 
 int get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt7601u_extra_power_over_mac (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mt7601u_save_power_rate (struct mt7601u_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mt7601u_wr (struct mt7601u_dev*,scalar_t__,int) ; 

__attribute__((used)) static void
mt7601u_config_tx_power_per_rate(struct mt7601u_dev *dev, u8 *eeprom)
{
	u32 val;
	s8 bw40_delta;
	int i;

	bw40_delta = get_delta(eeprom[MT_EE_TX_POWER_DELTA_BW40]);

	for (i = 0; i < 5; i++) {
		val = get_unaligned_le32(eeprom + MT_EE_TX_POWER_BYRATE(i));

		mt7601u_save_power_rate(dev, bw40_delta, val, i);

		if (~val)
			mt7601u_wr(dev, MT_TX_PWR_CFG_0 + i * 4, val);
	}

	mt7601u_extra_power_over_mac(dev);
}