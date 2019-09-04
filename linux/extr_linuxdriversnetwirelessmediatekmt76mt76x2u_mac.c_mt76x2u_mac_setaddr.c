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
struct TYPE_2__ {scalar_t__ macaddr; int /*<<< orphan*/  dev; } ;
struct mt76x2_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_MAC_ADDR_DW0 ; 
 int /*<<< orphan*/  MT_MAC_ADDR_DW1 ; 
 int /*<<< orphan*/  MT_MAC_ADDR_DW1_U2ME_MASK ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  eth_random_addr (scalar_t__) ; 
 int /*<<< orphan*/  ether_addr_copy (scalar_t__,int /*<<< orphan*/ *) ; 
 int get_unaligned_le16 (scalar_t__) ; 
 int get_unaligned_le32 (scalar_t__) ; 
 int /*<<< orphan*/  is_valid_ether_addr (scalar_t__) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x2_dev*,int /*<<< orphan*/ ,int) ; 

void mt76x2u_mac_setaddr(struct mt76x2_dev *dev, u8 *addr)
{
	ether_addr_copy(dev->mt76.macaddr, addr);

	if (!is_valid_ether_addr(dev->mt76.macaddr)) {
		eth_random_addr(dev->mt76.macaddr);
		dev_info(dev->mt76.dev,
			 "Invalid MAC address, using random address %pM\n",
			 dev->mt76.macaddr);
	}

	mt76_wr(dev, MT_MAC_ADDR_DW0, get_unaligned_le32(dev->mt76.macaddr));
	mt76_wr(dev, MT_MAC_ADDR_DW1,
		get_unaligned_le16(dev->mt76.macaddr + 4) |
		FIELD_PREP(MT_MAC_ADDR_DW1_U2ME_MASK, 0xff));
}