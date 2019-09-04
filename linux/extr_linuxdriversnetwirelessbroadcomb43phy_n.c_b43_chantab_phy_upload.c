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
struct b43_wldev {int dummy; } ;
struct b43_phy_n_sfo_cfg {int /*<<< orphan*/  phy_bw6; int /*<<< orphan*/  phy_bw5; int /*<<< orphan*/  phy_bw4; int /*<<< orphan*/  phy_bw3; int /*<<< orphan*/  phy_bw2; int /*<<< orphan*/  phy_bw1a; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NPHY_BW1A ; 
 int /*<<< orphan*/  B43_NPHY_BW2 ; 
 int /*<<< orphan*/  B43_NPHY_BW3 ; 
 int /*<<< orphan*/  B43_NPHY_BW4 ; 
 int /*<<< orphan*/  B43_NPHY_BW5 ; 
 int /*<<< orphan*/  B43_NPHY_BW6 ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_chantab_phy_upload(struct b43_wldev *dev,
				   const struct b43_phy_n_sfo_cfg *e)
{
	b43_phy_write(dev, B43_NPHY_BW1A, e->phy_bw1a);
	b43_phy_write(dev, B43_NPHY_BW2, e->phy_bw2);
	b43_phy_write(dev, B43_NPHY_BW3, e->phy_bw3);
	b43_phy_write(dev, B43_NPHY_BW4, e->phy_bw4);
	b43_phy_write(dev, B43_NPHY_BW5, e->phy_bw5);
	b43_phy_write(dev, B43_NPHY_BW6, e->phy_bw6);
}