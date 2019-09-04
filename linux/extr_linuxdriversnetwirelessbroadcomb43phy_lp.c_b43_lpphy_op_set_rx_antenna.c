#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rev; TYPE_1__* lp; } ;
struct b43_wldev {TYPE_2__ phy; } ;
struct TYPE_3__ {int antenna; } ;

/* Variables and functions */
 int B43_ANTENNA_AUTO1 ; 
 int B43_HF_ANTDIVHELP ; 
 int /*<<< orphan*/  B43_LPPHY_CRSGAIN_CTL ; 
 scalar_t__ B43_WARN_ON (int) ; 
 int b43_hf_read (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_hf_write (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void b43_lpphy_op_set_rx_antenna(struct b43_wldev *dev, int antenna)
{
	if (dev->phy.rev >= 2)
		return; // rev2+ doesn't support antenna diversity

	if (B43_WARN_ON(antenna > B43_ANTENNA_AUTO1))
		return;

	b43_hf_write(dev, b43_hf_read(dev) & ~B43_HF_ANTDIVHELP);

	b43_phy_maskset(dev, B43_LPPHY_CRSGAIN_CTL, 0xFFFD, antenna & 0x2);
	b43_phy_maskset(dev, B43_LPPHY_CRSGAIN_CTL, 0xFFFE, antenna & 0x1);

	b43_hf_write(dev, b43_hf_read(dev) | B43_HF_ANTDIVHELP);

	dev->phy.lp->antenna = antenna;
}