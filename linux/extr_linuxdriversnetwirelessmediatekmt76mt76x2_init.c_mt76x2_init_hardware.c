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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct mt76x2_dev {int const* beacon_offsets; TYPE_1__ mt76; void* rxfilter; int /*<<< orphan*/  pre_tbtt_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_STATE_INITIALIZED ; 
 int /*<<< orphan*/  MT_RX_FILTR_CFG ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG ; 
 int MT_WPDMA_GLO_CFG_BIG_ENDIAN ; 
 int MT_WPDMA_GLO_CFG_DMA_BURST_SIZE ; 
 int MT_WPDMA_GLO_CFG_HDR_SEG_LEN ; 
 int MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE ; 
 void* mt76_rr (struct mt76x2_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x2_dev*,int /*<<< orphan*/ ,int) ; 
 int mt76x2_dma_init (struct mt76x2_dev*) ; 
 int mt76x2_eeprom_init (struct mt76x2_dev*) ; 
 int mt76x2_mac_reset (struct mt76x2_dev*,int) ; 
 int mt76x2_mac_start (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2_mac_stop (struct mt76x2_dev*,int) ; 
 int mt76x2_mcu_init (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2_power_on (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2_pre_tbtt_tasklet ; 
 int /*<<< orphan*/  mt76x2_reset_wlan (struct mt76x2_dev*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

int mt76x2_init_hardware(struct mt76x2_dev *dev)
{
	static const u16 beacon_offsets[16] = {
		/* 1024 byte per beacon */
		0xc000,
		0xc400,
		0xc800,
		0xcc00,
		0xd000,
		0xd400,
		0xd800,
		0xdc00,

		/* BSS idx 8-15 not used for beacons */
		0xc000,
		0xc000,
		0xc000,
		0xc000,
		0xc000,
		0xc000,
		0xc000,
		0xc000,
	};
	u32 val;
	int ret;

	dev->beacon_offsets = beacon_offsets;
	tasklet_init(&dev->pre_tbtt_tasklet, mt76x2_pre_tbtt_tasklet,
		     (unsigned long) dev);

	val = mt76_rr(dev, MT_WPDMA_GLO_CFG);
	val &= MT_WPDMA_GLO_CFG_DMA_BURST_SIZE |
	       MT_WPDMA_GLO_CFG_BIG_ENDIAN |
	       MT_WPDMA_GLO_CFG_HDR_SEG_LEN;
	val |= MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE;
	mt76_wr(dev, MT_WPDMA_GLO_CFG, val);

	mt76x2_reset_wlan(dev, true);
	mt76x2_power_on(dev);

	ret = mt76x2_eeprom_init(dev);
	if (ret)
		return ret;

	ret = mt76x2_mac_reset(dev, true);
	if (ret)
		return ret;

	dev->rxfilter = mt76_rr(dev, MT_RX_FILTR_CFG);

	ret = mt76x2_dma_init(dev);
	if (ret)
		return ret;

	set_bit(MT76_STATE_INITIALIZED, &dev->mt76.state);
	ret = mt76x2_mac_start(dev);
	if (ret)
		return ret;

	ret = mt76x2_mcu_init(dev);
	if (ret)
		return ret;

	mt76x2_mac_stop(dev, false);

	return 0;
}