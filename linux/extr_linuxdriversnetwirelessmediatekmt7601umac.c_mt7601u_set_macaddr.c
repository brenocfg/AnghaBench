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
struct mt7601u_dev {scalar_t__ macaddr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_MAC_ADDR_DW0 ; 
 int /*<<< orphan*/  MT_MAC_ADDR_DW1 ; 
 int /*<<< orphan*/  MT_MAC_ADDR_DW1_U2ME_MASK ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  eth_random_addr (scalar_t__) ; 
 int /*<<< orphan*/  ether_addr_copy (scalar_t__,int /*<<< orphan*/  const*) ; 
 int get_unaligned_le16 (scalar_t__) ; 
 int get_unaligned_le32 (scalar_t__) ; 
 int /*<<< orphan*/  is_valid_ether_addr (scalar_t__) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int) ; 

void mt7601u_set_macaddr(struct mt7601u_dev *dev, const u8 *addr)
{
	ether_addr_copy(dev->macaddr, addr);

	if (!is_valid_ether_addr(dev->macaddr)) {
		eth_random_addr(dev->macaddr);
		dev_info(dev->dev,
			 "Invalid MAC address, using random address %pM\n",
			 dev->macaddr);
	}

	mt76_wr(dev, MT_MAC_ADDR_DW0, get_unaligned_le32(dev->macaddr));
	mt76_wr(dev, MT_MAC_ADDR_DW1, get_unaligned_le16(dev->macaddr + 4) |
		FIELD_PREP(MT_MAC_ADDR_DW1_U2ME_MASK, 0xff));
}