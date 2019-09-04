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
struct lpphy_stx_table_entry {int rf_shift; int phy_shift; int mask; scalar_t__ phy_offset; int /*<<< orphan*/  rf_addr; } ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct lpphy_stx_table_entry*) ; 
 int /*<<< orphan*/  B43_PHY_OFDM (scalar_t__) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_radio_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 struct lpphy_stx_table_entry* lpphy_stx_table ; 

__attribute__((used)) static void lpphy_sync_stx(struct b43_wldev *dev)
{
	const struct lpphy_stx_table_entry *e;
	unsigned int i;
	u16 tmp;

	for (i = 0; i < ARRAY_SIZE(lpphy_stx_table); i++) {
		e = &lpphy_stx_table[i];
		tmp = b43_radio_read(dev, e->rf_addr);
		tmp >>= e->rf_shift;
		tmp <<= e->phy_shift;
		b43_phy_maskset(dev, B43_PHY_OFDM(0xF2 + e->phy_offset),
				~(e->mask << e->phy_shift), tmp);
	}
}