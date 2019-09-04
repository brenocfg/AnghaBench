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
typedef  int u32 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
#define  B43_LCNTAB_16BIT 130 
#define  B43_LCNTAB_32BIT 129 
#define  B43_LCNTAB_8BIT 128 
 int B43_LCNTAB_TYPEMASK ; 
 int /*<<< orphan*/  B43_PHY_LCN_TABLE_ADDR ; 
 int /*<<< orphan*/  B43_PHY_LCN_TABLE_DATAHI ; 
 int /*<<< orphan*/  B43_PHY_LCN_TABLE_DATALO ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

u32 b43_lcntab_read(struct b43_wldev *dev, u32 offset)
{
	u32 type, value;

	type = offset & B43_LCNTAB_TYPEMASK;
	offset &= ~B43_LCNTAB_TYPEMASK;
	B43_WARN_ON(offset > 0xFFFF);

	switch (type) {
	case B43_LCNTAB_8BIT:
		b43_phy_write(dev, B43_PHY_LCN_TABLE_ADDR, offset);
		value = b43_phy_read(dev, B43_PHY_LCN_TABLE_DATALO) & 0xFF;
		break;
	case B43_LCNTAB_16BIT:
		b43_phy_write(dev, B43_PHY_LCN_TABLE_ADDR, offset);
		value = b43_phy_read(dev, B43_PHY_LCN_TABLE_DATALO);
		break;
	case B43_LCNTAB_32BIT:
		b43_phy_write(dev, B43_PHY_LCN_TABLE_ADDR, offset);
		value = b43_phy_read(dev, B43_PHY_LCN_TABLE_DATALO);
		value |= (b43_phy_read(dev, B43_PHY_LCN_TABLE_DATAHI) << 16);
		break;
	default:
		B43_WARN_ON(1);
		value = 0;
	}

	return value;
}