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
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_AUX_CLK_CFG ; 
 int /*<<< orphan*/  MT_MCU_MEMMAP_WLAN ; 
 int /*<<< orphan*/  mac_chip_vals ; 
 int /*<<< orphan*/  mac_common_vals ; 
 int /*<<< orphan*/  mt7601u_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt7601u_write_reg_pairs (struct mt7601u_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_init_beacon_offsets (struct mt7601u_dev*) ; 

__attribute__((used)) static int mt7601u_write_mac_initvals(struct mt7601u_dev *dev)
{
	int ret;

	ret = mt7601u_write_reg_pairs(dev, MT_MCU_MEMMAP_WLAN, mac_common_vals,
				      ARRAY_SIZE(mac_common_vals));
	if (ret)
		return ret;
	ret = mt7601u_write_reg_pairs(dev, MT_MCU_MEMMAP_WLAN,
				      mac_chip_vals, ARRAY_SIZE(mac_chip_vals));
	if (ret)
		return ret;

	mt76_init_beacon_offsets(dev);

	mt7601u_wr(dev, MT_AUX_CLK_CFG, 0);

	return 0;
}