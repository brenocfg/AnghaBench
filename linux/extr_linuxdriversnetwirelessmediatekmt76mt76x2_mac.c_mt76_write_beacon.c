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
typedef  int /*<<< orphan*/  txwi ;
struct sk_buff {int len; struct mt76x2_txwi* data; } ;
struct mt76x2_txwi {int dummy; } ;
struct mt76x2_dev {int* beacon_offsets; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  mt76_wr_copy (struct mt76x2_dev*,int,struct mt76x2_txwi*,int) ; 
 int /*<<< orphan*/  mt76x2_mac_write_txwi (struct mt76x2_dev*,struct mt76x2_txwi*,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
mt76_write_beacon(struct mt76x2_dev *dev, int offset, struct sk_buff *skb)
{
	int beacon_len = dev->beacon_offsets[1] - dev->beacon_offsets[0];
	struct mt76x2_txwi txwi;

	if (WARN_ON_ONCE(beacon_len < skb->len + sizeof(struct mt76x2_txwi)))
		return -ENOSPC;

	mt76x2_mac_write_txwi(dev, &txwi, skb, NULL, NULL, skb->len);

	mt76_wr_copy(dev, offset, &txwi, sizeof(txwi));
	offset += sizeof(txwi);

	mt76_wr_copy(dev, offset, skb->data, skb->len);
	return 0;
}