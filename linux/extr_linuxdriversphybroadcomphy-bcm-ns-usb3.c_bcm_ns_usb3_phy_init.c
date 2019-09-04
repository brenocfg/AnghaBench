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
struct phy {int dummy; } ;
struct bcm_ns_usb3 {int family; scalar_t__ dmp; } ;

/* Variables and functions */
 scalar_t__ BCMA_RESET_CTL ; 
 int /*<<< orphan*/  BCMA_RESET_CTL_RESET ; 
#define  BCM_NS_AX 129 
#define  BCM_NS_BX 128 
 int ENOTSUPP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int bcm_ns_usb3_phy_init_ns_ax (struct bcm_ns_usb3*) ; 
 int bcm_ns_usb3_phy_init_ns_bx (struct bcm_ns_usb3*) ; 
 struct bcm_ns_usb3* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int bcm_ns_usb3_phy_init(struct phy *phy)
{
	struct bcm_ns_usb3 *usb3 = phy_get_drvdata(phy);
	int err;

	/* Perform USB3 system soft reset */
	writel(BCMA_RESET_CTL_RESET, usb3->dmp + BCMA_RESET_CTL);

	switch (usb3->family) {
	case BCM_NS_AX:
		err = bcm_ns_usb3_phy_init_ns_ax(usb3);
		break;
	case BCM_NS_BX:
		err = bcm_ns_usb3_phy_init_ns_bx(usb3);
		break;
	default:
		WARN_ON(1);
		err = -ENOTSUPP;
	}

	return err;
}