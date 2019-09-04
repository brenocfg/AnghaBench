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
typedef  int /*<<< orphan*/  u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void check_phyreg(struct b43_wldev *dev, u16 offset)
{
#if B43_DEBUG
	if ((offset & B43_PHYROUTE) == B43_PHYROUTE_OFDM_GPHY) {
		/* OFDM registers are onnly available on A/G-PHYs */
		b43err(dev->wl, "Invalid OFDM PHY access at "
		       "0x%04X on N-PHY\n", offset);
		dump_stack();
	}
	if ((offset & B43_PHYROUTE) == B43_PHYROUTE_EXT_GPHY) {
		/* Ext-G registers are only available on G-PHYs */
		b43err(dev->wl, "Invalid EXT-G PHY access at "
		       "0x%04X on N-PHY\n", offset);
		dump_stack();
	}
#endif /* B43_DEBUG */
}