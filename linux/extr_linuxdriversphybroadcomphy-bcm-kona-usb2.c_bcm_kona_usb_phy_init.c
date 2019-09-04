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
struct phy {int dummy; } ;
struct bcm_kona_usb {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ P1CTL ; 
 int P1CTL_NON_DRIVING ; 
 int P1CTL_SOFT_RESET ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct bcm_kona_usb* phy_get_drvdata (struct phy*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int bcm_kona_usb_phy_init(struct phy *gphy)
{
	struct bcm_kona_usb *phy = phy_get_drvdata(gphy);
	u32 val;

	/* Soft reset PHY */
	val = readl(phy->regs + P1CTL);
	val &= ~P1CTL_NON_DRIVING;
	val |= P1CTL_SOFT_RESET;
	writel(val, phy->regs + P1CTL);
	writel(val & ~P1CTL_SOFT_RESET, phy->regs + P1CTL);
	/* Reset needs to be asserted for 2ms */
	mdelay(2);
	writel(val | P1CTL_SOFT_RESET, phy->regs + P1CTL);

	return 0;
}