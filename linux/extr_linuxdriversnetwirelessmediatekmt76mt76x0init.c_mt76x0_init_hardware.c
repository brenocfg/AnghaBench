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
typedef  int u16 ;
struct mt76x0_dev {int const* beacon_offsets; } ;

/* Variables and functions */
 int EIO ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_BEACON_TIME_CFG ; 
 int MT_BEACON_TIME_CFG_BEACON_TX ; 
 int MT_BEACON_TIME_CFG_SYNC_MODE ; 
 int MT_BEACON_TIME_CFG_TBTT_EN ; 
 int MT_BEACON_TIME_CFG_TIMER_EN ; 
 int /*<<< orphan*/  MT_HEADER_TRANS_CTRL_REG ; 
 int /*<<< orphan*/  MT_MAC_STATUS ; 
 int MT_MAC_STATUS_RX ; 
 int MT_MAC_STATUS_TX ; 
 int /*<<< orphan*/  MT_TSO_CTRL ; 
 int /*<<< orphan*/  MT_TXOP_CTRL_CFG ; 
 int /*<<< orphan*/  MT_TXOP_EXT_CCA_DLY ; 
 int /*<<< orphan*/  MT_TXOP_TRUN_EN ; 
 int /*<<< orphan*/  MT_US_CYC_CFG ; 
 int /*<<< orphan*/  MT_US_CYC_CNT ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG ; 
 int MT_WPDMA_GLO_CFG_RX_DMA_BUSY ; 
 int MT_WPDMA_GLO_CFG_TX_DMA_BUSY ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_poll_msec (struct mt76x0_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_rmw (struct mt76x0_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x0_chip_onoff (struct mt76x0_dev*,int,int) ; 
 int /*<<< orphan*/  mt76x0_dma_cleanup (struct mt76x0_dev*) ; 
 int mt76x0_dma_init (struct mt76x0_dev*) ; 
 int mt76x0_eeprom_init (struct mt76x0_dev*) ; 
 int mt76x0_init_bbp (struct mt76x0_dev*) ; 
 int mt76x0_init_key_mem (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  mt76x0_init_mac_registers (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  mt76x0_init_usb_dma (struct mt76x0_dev*) ; 
 int mt76x0_init_wcid_attr_mem (struct mt76x0_dev*) ; 
 int mt76x0_init_wcid_mem (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  mt76x0_mcu_cmd_deinit (struct mt76x0_dev*) ; 
 int mt76x0_mcu_cmd_init (struct mt76x0_dev*) ; 
 int mt76x0_mcu_init (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  mt76x0_phy_init (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  mt76x0_reset_counters (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  mt76x0_reset_csr_bbp (struct mt76x0_dev*) ; 
 int mt76x0_wait_asic_ready (struct mt76x0_dev*) ; 

int mt76x0_init_hardware(struct mt76x0_dev *dev)
{
	static const u16 beacon_offsets[16] = {
		/* 512 byte per beacon */
		0xc000,	0xc200,	0xc400,	0xc600,
		0xc800,	0xca00,	0xcc00,	0xce00,
		0xd000,	0xd200,	0xd400,	0xd600,
		0xd800,	0xda00,	0xdc00,	0xde00
	};
	int ret;

	dev->beacon_offsets = beacon_offsets;

	mt76x0_chip_onoff(dev, true, true);

	ret = mt76x0_wait_asic_ready(dev);
	if (ret)
		goto err;
	ret = mt76x0_mcu_init(dev);
	if (ret)
		goto err;

	if (!mt76_poll_msec(dev, MT_WPDMA_GLO_CFG,
			    MT_WPDMA_GLO_CFG_TX_DMA_BUSY |
			    MT_WPDMA_GLO_CFG_RX_DMA_BUSY, 0, 100)) {
		ret = -EIO;
		goto err;
	}

	/* Wait for ASIC ready after FW load. */
	ret = mt76x0_wait_asic_ready(dev);
	if (ret)
		goto err;

	mt76x0_reset_csr_bbp(dev);
	mt76x0_init_usb_dma(dev);

	mt76_wr(dev, MT_HEADER_TRANS_CTRL_REG, 0x0);
	mt76_wr(dev, MT_TSO_CTRL, 0x0);

	ret = mt76x0_mcu_cmd_init(dev);
	if (ret)
		goto err;
	ret = mt76x0_dma_init(dev);
	if (ret)
		goto err_mcu;

	mt76x0_init_mac_registers(dev);

	if (!mt76_poll_msec(dev, MT_MAC_STATUS,
			    MT_MAC_STATUS_TX | MT_MAC_STATUS_RX, 0, 1000)) {
		ret = -EIO;
		goto err_rx;
	}

	ret = mt76x0_init_bbp(dev);
	if (ret)
		goto err_rx;

	ret = mt76x0_init_wcid_mem(dev);
	if (ret)
		goto err_rx;
	ret = mt76x0_init_key_mem(dev);
	if (ret)
		goto err_rx;
	ret = mt76x0_init_wcid_attr_mem(dev);
	if (ret)
		goto err_rx;

	mt76_clear(dev, MT_BEACON_TIME_CFG, (MT_BEACON_TIME_CFG_TIMER_EN |
					     MT_BEACON_TIME_CFG_SYNC_MODE |
					     MT_BEACON_TIME_CFG_TBTT_EN |
					     MT_BEACON_TIME_CFG_BEACON_TX));

	mt76x0_reset_counters(dev);

	mt76_rmw(dev, MT_US_CYC_CFG, MT_US_CYC_CNT, 0x1e);

	mt76_wr(dev, MT_TXOP_CTRL_CFG,
		   FIELD_PREP(MT_TXOP_TRUN_EN, 0x3f) |
		   FIELD_PREP(MT_TXOP_EXT_CCA_DLY, 0x58));

	ret = mt76x0_eeprom_init(dev);
	if (ret)
		goto err_rx;

	mt76x0_phy_init(dev);
	return 0;

err_rx:
	mt76x0_dma_cleanup(dev);
err_mcu:
	mt76x0_mcu_cmd_deinit(dev);
err:
	mt76x0_chip_onoff(dev, false, false);
	return ret;
}