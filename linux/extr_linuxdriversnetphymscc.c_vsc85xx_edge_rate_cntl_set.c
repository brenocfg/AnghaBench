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
struct phy_device {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EDGE_RATE_CNTL_MASK ; 
 int EDGE_RATE_CNTL_POS ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_EXTENDED_2 ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_STANDARD ; 
 int /*<<< orphan*/  MSCC_PHY_WOL_MAC_CONTROL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int vsc85xx_phy_page_set (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsc85xx_edge_rate_cntl_set(struct phy_device *phydev, u8 edge_rate)
{
	int rc;
	u16 reg_val;

	mutex_lock(&phydev->lock);
	rc = vsc85xx_phy_page_set(phydev, MSCC_PHY_PAGE_EXTENDED_2);
	if (rc != 0)
		goto out_unlock;
	reg_val = phy_read(phydev, MSCC_PHY_WOL_MAC_CONTROL);
	reg_val &= ~(EDGE_RATE_CNTL_MASK);
	reg_val |= (edge_rate << EDGE_RATE_CNTL_POS);
	rc = phy_write(phydev, MSCC_PHY_WOL_MAC_CONTROL, reg_val);
	if (rc != 0)
		goto out_unlock;
	rc = vsc85xx_phy_page_set(phydev, MSCC_PHY_PAGE_STANDARD);

out_unlock:
	mutex_unlock(&phydev->lock);

	return rc;
}