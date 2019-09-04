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
struct miphy28lp_phy {scalar_t__ pipebase; int /*<<< orphan*/  base; struct miphy28lp_dev* phydev; } ;
struct miphy28lp_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MIPHY_CTRL_SYNC_D_EN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  miphy28lp_configure_usb3 (struct miphy28lp_phy*) ; 
 int miphy28lp_setup (struct miphy28lp_phy*,int /*<<< orphan*/ ) ; 
 int miphy_is_ready (struct miphy28lp_phy*) ; 
 int /*<<< orphan*/  writeb_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int miphy28lp_init_usb3(struct miphy28lp_phy *miphy_phy)
{
	struct miphy28lp_dev *miphy_dev = miphy_phy->phydev;
	int err;

	if ((!miphy_phy->base) || (!miphy_phy->pipebase))
		return -EINVAL;

	dev_info(miphy_dev->dev, "usb3-up mode, addr 0x%p\n", miphy_phy->base);

	/* MiPHY path and clocking init */
	err = miphy28lp_setup(miphy_phy, MIPHY_CTRL_SYNC_D_EN);
	if (err) {
		dev_err(miphy_dev->dev, "USB3 phy setup failed\n");
		return err;
	}

	/* initialize miphy */
	miphy28lp_configure_usb3(miphy_phy);

	/* PIPE Wrapper Configuration */
	writeb_relaxed(0x68, miphy_phy->pipebase + 0x23);
	writeb_relaxed(0x61, miphy_phy->pipebase + 0x24);
	writeb_relaxed(0x68, miphy_phy->pipebase + 0x26);
	writeb_relaxed(0x61, miphy_phy->pipebase + 0x27);
	writeb_relaxed(0x18, miphy_phy->pipebase + 0x29);
	writeb_relaxed(0x61, miphy_phy->pipebase + 0x2a);

	/* pipe Wrapper usb3 TX swing de-emph margin PREEMPH[7:4], SWING[3:0] */
	writeb_relaxed(0X67, miphy_phy->pipebase + 0x68);
	writeb_relaxed(0x0d, miphy_phy->pipebase + 0x69);
	writeb_relaxed(0X67, miphy_phy->pipebase + 0x6a);
	writeb_relaxed(0X0d, miphy_phy->pipebase + 0x6b);
	writeb_relaxed(0X67, miphy_phy->pipebase + 0x6c);
	writeb_relaxed(0X0d, miphy_phy->pipebase + 0x6d);
	writeb_relaxed(0X67, miphy_phy->pipebase + 0x6e);
	writeb_relaxed(0X0d, miphy_phy->pipebase + 0x6f);

	return miphy_is_ready(miphy_phy);
}