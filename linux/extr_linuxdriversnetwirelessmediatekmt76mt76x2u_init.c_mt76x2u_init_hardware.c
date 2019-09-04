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
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ data; } ;
struct TYPE_4__ {TYPE_1__ eeprom; } ;
struct mt76x2_dev {int const* beacon_offsets; int /*<<< orphan*/  rxfilter; TYPE_2__ mt76; } ;
struct mt76_wcid_addr {int /*<<< orphan*/  ba_mask; int /*<<< orphan*/  macaddr; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MT_BEACON_TIME_CFG ; 
 int MT_BEACON_TIME_CFG_BEACON_TX ; 
 int MT_BEACON_TIME_CFG_SYNC_MODE ; 
 int MT_BEACON_TIME_CFG_TBTT_EN ; 
 int MT_BEACON_TIME_CFG_TIMER_EN ; 
 scalar_t__ MT_EE_MAC_ADDR ; 
 scalar_t__ MT_HEADER_TRANS_CTRL_REG ; 
 int /*<<< orphan*/  MT_RF_BBP_CR ; 
 int /*<<< orphan*/  MT_RX_FILTR_CFG ; 
 scalar_t__ MT_SKEY_MODE_BASE_0 ; 
 scalar_t__ MT_TSO_CTRL ; 
 scalar_t__ MT_TXOP_CTRL_CFG ; 
 int /*<<< orphan*/  MT_US_CYC_CFG ; 
 int /*<<< orphan*/  MT_US_CYC_CNT ; 
 int /*<<< orphan*/  MT_WCID_ADDR (int) ; 
 scalar_t__ MT_WCID_ATTR (int) ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG ; 
 int MT_WPDMA_GLO_CFG_RX_DMA_BUSY ; 
 int MT_WPDMA_GLO_CFG_TX_DMA_BUSY ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x2_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_poll_msec (struct mt76x2_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_rmw (struct mt76x2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x2_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x2_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  mt76_wr_copy (struct mt76x2_dev*,int /*<<< orphan*/ ,struct mt76_wcid_addr const*,int) ; 
 int /*<<< orphan*/  mt76x2_reset_wlan (struct mt76x2_dev*,int) ; 
 int /*<<< orphan*/  mt76x2_wait_for_bbp (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2_wait_for_mac (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2u_init_beacon_offsets (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2u_init_dma (struct mt76x2_dev*) ; 
 int mt76x2u_mac_reset (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2u_mac_setaddr (struct mt76x2_dev*,scalar_t__) ; 
 int mt76x2u_mac_stop (struct mt76x2_dev*) ; 
 int mt76x2u_mcu_fw_init (struct mt76x2_dev*) ; 
 int mt76x2u_mcu_init (struct mt76x2_dev*) ; 
 int mt76x2u_mcu_load_cr (struct mt76x2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x2u_phy_set_rxpath (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2u_phy_set_txdac (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2u_power_on (struct mt76x2_dev*) ; 

int mt76x2u_init_hardware(struct mt76x2_dev *dev)
{
	static const u16 beacon_offsets[] = {
		/* 512 byte per beacon */
		0xc000, 0xc200, 0xc400, 0xc600,
		0xc800, 0xca00, 0xcc00, 0xce00,
		0xd000, 0xd200, 0xd400, 0xd600,
		0xd800, 0xda00, 0xdc00, 0xde00
	};
	const struct mt76_wcid_addr addr = {
		.macaddr = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
		.ba_mask = 0,
	};
	int i, err;

	dev->beacon_offsets = beacon_offsets;

	mt76x2_reset_wlan(dev, true);
	mt76x2u_power_on(dev);

	if (!mt76x2_wait_for_mac(dev))
		return -ETIMEDOUT;

	err = mt76x2u_mcu_fw_init(dev);
	if (err < 0)
		return err;

	if (!mt76_poll_msec(dev, MT_WPDMA_GLO_CFG,
			    MT_WPDMA_GLO_CFG_TX_DMA_BUSY |
			    MT_WPDMA_GLO_CFG_RX_DMA_BUSY, 0, 100))
		return -EIO;

	/* wait for asic ready after fw load. */
	if (!mt76x2_wait_for_mac(dev))
		return -ETIMEDOUT;

	mt76_wr(dev, MT_HEADER_TRANS_CTRL_REG, 0);
	mt76_wr(dev, MT_TSO_CTRL, 0);

	mt76x2u_init_dma(dev);

	err = mt76x2u_mcu_init(dev);
	if (err < 0)
		return err;

	err = mt76x2u_mac_reset(dev);
	if (err < 0)
		return err;

	mt76x2u_mac_setaddr(dev, dev->mt76.eeprom.data + MT_EE_MAC_ADDR);
	dev->rxfilter = mt76_rr(dev, MT_RX_FILTR_CFG);

	mt76x2u_init_beacon_offsets(dev);

	if (!mt76x2_wait_for_bbp(dev))
		return -ETIMEDOUT;

	/* reset wcid table */
	for (i = 0; i < 254; i++)
		mt76_wr_copy(dev, MT_WCID_ADDR(i), &addr,
			     sizeof(struct mt76_wcid_addr));

	/* reset shared key table and pairwise key table */
	for (i = 0; i < 4; i++)
		mt76_wr(dev, MT_SKEY_MODE_BASE_0 + 4 * i, 0);
	for (i = 0; i < 256; i++)
		mt76_wr(dev, MT_WCID_ATTR(i), 1);

	mt76_clear(dev, MT_BEACON_TIME_CFG,
		   MT_BEACON_TIME_CFG_TIMER_EN |
		   MT_BEACON_TIME_CFG_SYNC_MODE |
		   MT_BEACON_TIME_CFG_TBTT_EN |
		   MT_BEACON_TIME_CFG_BEACON_TX);

	mt76_rmw(dev, MT_US_CYC_CFG, MT_US_CYC_CNT, 0x1e);
	mt76_wr(dev, MT_TXOP_CTRL_CFG, 0x583f);

	err = mt76x2u_mcu_load_cr(dev, MT_RF_BBP_CR, 0, 0);
	if (err < 0)
		return err;

	mt76x2u_phy_set_rxpath(dev);
	mt76x2u_phy_set_txdac(dev);

	return mt76x2u_mac_stop(dev);
}