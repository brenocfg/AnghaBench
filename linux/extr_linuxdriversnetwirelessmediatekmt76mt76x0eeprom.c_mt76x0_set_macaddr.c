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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mt76x0_dev {scalar_t__ macaddr; TYPE_1__ mt76; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int MT_EE_MAC_ADDR ; 
 int /*<<< orphan*/  MT_MAC_ADDR_DW0 ; 
 int /*<<< orphan*/  MT_MAC_ADDR_DW1 ; 
 int /*<<< orphan*/  MT_MAC_ADDR_DW1_U2ME_MASK ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  eth_random_addr (scalar_t__) ; 
 int /*<<< orphan*/  ether_addr_copy (scalar_t__,void const*) ; 
 int get_unaligned_le16 (scalar_t__) ; 
 int get_unaligned_le32 (scalar_t__) ; 
 int /*<<< orphan*/  is_valid_ether_addr (scalar_t__) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mt76x0_set_macaddr(struct mt76x0_dev *dev, const u8 *eeprom)
{
	const void *src = eeprom + MT_EE_MAC_ADDR;

	ether_addr_copy(dev->macaddr, src);

	if (!is_valid_ether_addr(dev->macaddr)) {
		eth_random_addr(dev->macaddr);
		dev_info(dev->mt76.dev,
			 "Invalid MAC address, using random address %pM\n",
			 dev->macaddr);
	}

	mt76_wr(dev, MT_MAC_ADDR_DW0, get_unaligned_le32(dev->macaddr));
	mt76_wr(dev, MT_MAC_ADDR_DW1, get_unaligned_le16(dev->macaddr + 4) |
		FIELD_PREP(MT_MAC_ADDR_DW1_U2ME_MASK, 0xff));

	return 0;
}