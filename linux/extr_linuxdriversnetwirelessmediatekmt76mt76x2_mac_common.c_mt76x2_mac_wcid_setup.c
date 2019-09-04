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
typedef  int u8 ;
typedef  int u32 ;
struct mt76x2_dev {int dummy; } ;
struct mt76_wcid_addr {int /*<<< orphan*/  macaddr; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_WCID_ADDR (int) ; 
 scalar_t__ MT_WCID_ATTR (int) ; 
 int /*<<< orphan*/  MT_WCID_ATTR_BSS_IDX ; 
 int /*<<< orphan*/  MT_WCID_ATTR_BSS_IDX_EXT ; 
 scalar_t__ MT_WCID_TX_RATE (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x2_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  mt76_wr_copy (struct mt76x2_dev*,int /*<<< orphan*/ ,struct mt76_wcid_addr*,int) ; 

void mt76x2_mac_wcid_setup(struct mt76x2_dev *dev, u8 idx, u8 vif_idx, u8 *mac)
{
	struct mt76_wcid_addr addr = {};
	u32 attr;

	attr = FIELD_PREP(MT_WCID_ATTR_BSS_IDX, vif_idx & 7) |
	       FIELD_PREP(MT_WCID_ATTR_BSS_IDX_EXT, !!(vif_idx & 8));

	mt76_wr(dev, MT_WCID_ATTR(idx), attr);

	mt76_wr(dev, MT_WCID_TX_RATE(idx), 0);
	mt76_wr(dev, MT_WCID_TX_RATE(idx) + 4, 0);

	if (idx >= 128)
		return;

	if (mac)
		memcpy(addr.macaddr, mac, ETH_ALEN);

	mt76_wr_copy(dev, MT_WCID_ADDR(idx), &addr, sizeof(addr));
}