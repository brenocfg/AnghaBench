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
typedef  int u32 ;
struct mt76x0_dev {int dummy; } ;

/* Variables and functions */
 int MT_COEXCFG0 ; 
 int MT_EXT_CCA_CFG ; 
 int /*<<< orphan*/  MT_FCE_L2_STUFF ; 
 int /*<<< orphan*/  MT_FCE_L2_STUFF_WR_MPDU_LEN_EN ; 
 int MT_MAC_SYS_CTRL ; 
 int MT_WMM_CTRL ; 
 int /*<<< orphan*/  RANDOM_WRITE (struct mt76x0_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common_mac_reg_table ; 
 scalar_t__ is_mt7610e (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x0_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_init_beacon_offsets (struct mt76x0_dev*) ; 
 int mt76_rr (struct mt76x0_dev*,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x0_dev*,int,int) ; 
 int /*<<< orphan*/  mt76x0_mac_reg_table ; 

__attribute__((used)) static void mt76x0_init_mac_registers(struct mt76x0_dev *dev)
{
	u32 reg;

	RANDOM_WRITE(dev, common_mac_reg_table);

	mt76_init_beacon_offsets(dev);

	/* Enable PBF and MAC clock SYS_CTRL[11:10] = 0x3 */
	RANDOM_WRITE(dev, mt76x0_mac_reg_table);

	/* Release BBP and MAC reset MAC_SYS_CTRL[1:0] = 0x0 */
	reg = mt76_rr(dev, MT_MAC_SYS_CTRL);
	reg &= ~0x3;
	mt76_wr(dev, MT_MAC_SYS_CTRL, reg);

	if (is_mt7610e(dev)) {
		/* Disable COEX_EN */
		reg = mt76_rr(dev, MT_COEXCFG0);
		reg &= 0xFFFFFFFE;
		mt76_wr(dev, MT_COEXCFG0, reg);
	}

	/* Set 0x141C[15:12]=0xF */
	reg = mt76_rr(dev, MT_EXT_CCA_CFG);
	reg |= 0x0000F000;
	mt76_wr(dev, MT_EXT_CCA_CFG, reg);

	mt76_clear(dev, MT_FCE_L2_STUFF, MT_FCE_L2_STUFF_WR_MPDU_LEN_EN);

	/*
		TxRing 9 is for Mgmt frame.
		TxRing 8 is for In-band command frame.
		WMM_RG0_TXQMA: This register setting is for FCE to define the rule of TxRing 9.
		WMM_RG1_TXQMA: This register setting is for FCE to define the rule of TxRing 8.
	*/
	reg = mt76_rr(dev, MT_WMM_CTRL);
	reg &= ~0x000003FF;
	reg |= 0x00000201;
	mt76_wr(dev, MT_WMM_CTRL, reg);

	/* TODO: Probably not needed */
	mt76_wr(dev, 0x7028, 0);
	mt76_wr(dev, 0x7010, 0);
	mt76_wr(dev, 0x7024, 0);
	msleep(10);
}