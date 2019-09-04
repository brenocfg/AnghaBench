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
typedef  int u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  B43_PHY_EXTG (int const) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_phy_ht_zero_extg(struct b43_wldev *dev)
{
	u8 i, j;
	static const u16 base[] = { 0x40, 0x60, 0x80 };

	for (i = 0; i < ARRAY_SIZE(base); i++) {
		for (j = 0; j < 4; j++)
			b43_phy_write(dev, B43_PHY_EXTG(base[i] + j), 0);
	}

	for (i = 0; i < ARRAY_SIZE(base); i++)
		b43_phy_write(dev, B43_PHY_EXTG(base[i] + 0xc), 0);
}