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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct mt76x0_dev {TYPE_1__* ee; } ;
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_2__ {int** tx_pwr_cfg_2g; int** tx_pwr_cfg_5g; } ;

/* Variables and functions */
 int MT_EE_TX_POWER_BYRATE (int) ; 
 size_t MT_EE_TX_POWER_DELTA_BW40 ; 
 void* calc_bw40_power_rate (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_delta (int /*<<< orphan*/ ) ; 
 int get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int get_unaligned_le32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt76x0_set_tx_power_per_rate(struct mt76x0_dev *dev, u8 *eeprom)
{
	s8 bw40_delta_2g, bw40_delta_5g;
	u32 val;
	int i;

	bw40_delta_2g = get_delta(eeprom[MT_EE_TX_POWER_DELTA_BW40]);
	bw40_delta_5g = get_delta(eeprom[MT_EE_TX_POWER_DELTA_BW40 + 1]);

	for (i = 0; i < 5; i++) {
		val = get_unaligned_le32(eeprom + MT_EE_TX_POWER_BYRATE(i));

		/* Skip last 16 bits. */
		if (i == 4)
			val &= 0x0000ffff;

		dev->ee->tx_pwr_cfg_2g[i][0] = val;
		dev->ee->tx_pwr_cfg_2g[i][1] = calc_bw40_power_rate(val, bw40_delta_2g);
	}

	/* Reading per rate tx power for 5 GHz band is a bit more complex. Note
	 * we mix 16 bit and 32 bit reads and sometimes do shifts.
	 */
	val = get_unaligned_le16(eeprom + 0x120);
	val <<= 16;
	dev->ee->tx_pwr_cfg_5g[0][0] = val;
	dev->ee->tx_pwr_cfg_5g[0][1] = calc_bw40_power_rate(val, bw40_delta_5g);

	val = get_unaligned_le32(eeprom + 0x122);
	dev->ee->tx_pwr_cfg_5g[1][0] = val;
	dev->ee->tx_pwr_cfg_5g[1][1] = calc_bw40_power_rate(val, bw40_delta_5g);

	val = get_unaligned_le16(eeprom + 0x126);
	dev->ee->tx_pwr_cfg_5g[2][0] = val;
	dev->ee->tx_pwr_cfg_5g[2][1] = calc_bw40_power_rate(val, bw40_delta_5g);

	val = get_unaligned_le16(eeprom + 0xec);
	val <<= 16;
	dev->ee->tx_pwr_cfg_5g[3][0] = val;
	dev->ee->tx_pwr_cfg_5g[3][1] = calc_bw40_power_rate(val, bw40_delta_5g);

	val = get_unaligned_le16(eeprom + 0xee);
	dev->ee->tx_pwr_cfg_5g[4][0] = val;
	dev->ee->tx_pwr_cfg_5g[4][1] = calc_bw40_power_rate(val, bw40_delta_5g);
}