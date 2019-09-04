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
struct b43_phy {int rev; struct b43_phy_g* g; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_phy_g {scalar_t__ cur_idle_tssi; scalar_t__ tgt_idle_tssi; } ;

/* Variables and functions */
 int B43_HF_HWPCTL ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_gphy_dc_lt_init (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_gphy_gain_lt_init (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_gphy_tssi_power_lt_init (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_has_hardware_pctl (struct b43_wldev*) ; 
 int b43_hf_read (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_hf_write (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 

__attribute__((used)) static void b43_hardware_pctl_init_gphy(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;

	if (!b43_has_hardware_pctl(dev)) {
		/* No hardware power control */
		b43_hf_write(dev, b43_hf_read(dev) & ~B43_HF_HWPCTL);
		return;
	}

	b43_phy_maskset(dev, 0x0036, 0xFFC0, (gphy->tgt_idle_tssi - gphy->cur_idle_tssi));
	b43_phy_maskset(dev, 0x0478, 0xFF00, (gphy->tgt_idle_tssi - gphy->cur_idle_tssi));
	b43_gphy_tssi_power_lt_init(dev);
	b43_gphy_gain_lt_init(dev);
	b43_phy_mask(dev, 0x0060, 0xFFBF);
	b43_phy_write(dev, 0x0014, 0x0000);

	B43_WARN_ON(phy->rev < 6);
	b43_phy_set(dev, 0x0478, 0x0800);
	b43_phy_mask(dev, 0x0478, 0xFEFF);
	b43_phy_mask(dev, 0x0801, 0xFFBF);

	b43_gphy_dc_lt_init(dev, 1);

	/* Enable hardware pctl in firmware. */
	b43_hf_write(dev, b43_hf_read(dev) | B43_HF_HWPCTL);
}