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
typedef  int u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_HTTAB16 (int,int) ; 
 int /*<<< orphan*/  B43_HTTAB32 (int,int) ; 
 int /*<<< orphan*/  B43_HTTAB8 (int,int) ; 
 int /*<<< orphan*/  B43_PHY_EXTG (int) ; 
 int b43_httab_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_httab_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_phy_ht_tx_power_fix(struct b43_wldev *dev)
{
	int i;

	for (i = 0; i < 3; i++) {
		u16 mask;
		u32 tmp = b43_httab_read(dev, B43_HTTAB32(26, 0xE8));

		if (0) /* FIXME */
			mask = 0x2 << (i * 4);
		else
			mask = 0;
		b43_phy_mask(dev, B43_PHY_EXTG(0x108), mask);

		b43_httab_write(dev, B43_HTTAB16(7, 0x110 + i), tmp >> 16);
		b43_httab_write(dev, B43_HTTAB8(13, 0x63 + (i * 4)),
				tmp & 0xFF);
		b43_httab_write(dev, B43_HTTAB8(13, 0x73 + (i * 4)),
				tmp & 0xFF);
	}
}