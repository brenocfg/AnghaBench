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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct mt76_queue* q_tx; } ;
struct mt76x2_dev {TYPE_1__ mt76; } ;
struct mt76_queue_buf {int len; int /*<<< orphan*/  addr; } ;
struct mt76_queue {int /*<<< orphan*/  lock; } ;
typedef  enum mt76_txq_id { ____Placeholder_mt76_txq_id } mt76_txq_id ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int CPU_TX_PORT ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_MCU_MSG_CMD_SEQ ; 
 int /*<<< orphan*/  MT_MCU_MSG_CMD_TYPE ; 
 int /*<<< orphan*/  MT_MCU_MSG_LEN ; 
 int /*<<< orphan*/  MT_MCU_MSG_PORT ; 
 int MT_MCU_MSG_TYPE_CMD ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_queue_add_buf (struct mt76x2_dev*,struct mt76_queue*,struct mt76_queue_buf*,int,int,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_queue_kick (struct mt76x2_dev*,struct mt76_queue*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int
mt76x2_tx_queue_mcu(struct mt76x2_dev *dev, enum mt76_txq_id qid,
		    struct sk_buff *skb, int cmd, int seq)
{
	struct mt76_queue *q = &dev->mt76.q_tx[qid];
	struct mt76_queue_buf buf;
	dma_addr_t addr;
	u32 tx_info;

	tx_info = MT_MCU_MSG_TYPE_CMD |
		  FIELD_PREP(MT_MCU_MSG_CMD_TYPE, cmd) |
		  FIELD_PREP(MT_MCU_MSG_CMD_SEQ, seq) |
		  FIELD_PREP(MT_MCU_MSG_PORT, CPU_TX_PORT) |
		  FIELD_PREP(MT_MCU_MSG_LEN, skb->len);

	addr = dma_map_single(dev->mt76.dev, skb->data, skb->len,
			      DMA_TO_DEVICE);
	if (dma_mapping_error(dev->mt76.dev, addr))
		return -ENOMEM;

	buf.addr = addr;
	buf.len = skb->len;
	spin_lock_bh(&q->lock);
	mt76_queue_add_buf(dev, q, &buf, 1, tx_info, skb, NULL);
	mt76_queue_kick(dev, q);
	spin_unlock_bh(&q->lock);

	return 0;
}