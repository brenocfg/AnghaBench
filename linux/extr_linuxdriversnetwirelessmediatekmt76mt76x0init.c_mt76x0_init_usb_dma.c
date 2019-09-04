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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mt76x0_dev {int in_max_packet; TYPE_1__ mt76; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_COM_REG0 ; 
 int /*<<< orphan*/  MT_USB_AGGR_SIZE_LIMIT ; 
 int /*<<< orphan*/  MT_USB_AGGR_TIMEOUT ; 
 int /*<<< orphan*/  MT_USB_DMA_CFG ; 
 int MT_USB_DMA_CFG_RX_BULK_AGG_EN ; 
 int /*<<< orphan*/  MT_USB_DMA_CFG_RX_BULK_AGG_LMT ; 
 int /*<<< orphan*/  MT_USB_DMA_CFG_RX_BULK_AGG_TOUT ; 
 int MT_USB_DMA_CFG_RX_BULK_EN ; 
 int MT_USB_DMA_CFG_RX_DROP_OR_PADDING ; 
 int MT_USB_DMA_CFG_TX_BULK_EN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int mt76_rr (struct mt76x0_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mt76x0_init_usb_dma(struct mt76x0_dev *dev)
{
	u32 val;

	val = mt76_rr(dev, MT_USB_DMA_CFG);

	val |= FIELD_PREP(MT_USB_DMA_CFG_RX_BULK_AGG_TOUT, MT_USB_AGGR_TIMEOUT) |
	       FIELD_PREP(MT_USB_DMA_CFG_RX_BULK_AGG_LMT, MT_USB_AGGR_SIZE_LIMIT) |
	       MT_USB_DMA_CFG_RX_BULK_EN |
	       MT_USB_DMA_CFG_TX_BULK_EN;
	if (dev->in_max_packet == 512)
		val |= MT_USB_DMA_CFG_RX_BULK_AGG_EN;
	mt76_wr(dev, MT_USB_DMA_CFG, val);

	val = mt76_rr(dev, MT_COM_REG0);
	if (val & 1)
		dev_dbg(dev->mt76.dev, "MCU not ready\n");

	val = mt76_rr(dev, MT_USB_DMA_CFG);

	val |= MT_USB_DMA_CFG_RX_DROP_OR_PADDING;
	mt76_wr(dev, MT_USB_DMA_CFG, val);
	val &= ~MT_USB_DMA_CFG_RX_DROP_OR_PADDING;
	mt76_wr(dev, MT_USB_DMA_CFG, val);
}