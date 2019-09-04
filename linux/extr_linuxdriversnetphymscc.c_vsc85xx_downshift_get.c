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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int DOWNSHIFT_CNTL_MASK ; 
 int DOWNSHIFT_CNTL_POS ; 
 int DOWNSHIFT_DEV_DISABLE ; 
 int DOWNSHIFT_EN ; 
 int /*<<< orphan*/  MSCC_PHY_ACTIPHY_CNTL ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_EXTENDED ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_STANDARD ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int vsc85xx_phy_page_set (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsc85xx_downshift_get(struct phy_device *phydev, u8 *count)
{
	int rc;
	u16 reg_val;

	rc = vsc85xx_phy_page_set(phydev, MSCC_PHY_PAGE_EXTENDED);
	if (rc != 0)
		goto out;

	reg_val = phy_read(phydev, MSCC_PHY_ACTIPHY_CNTL);
	reg_val &= DOWNSHIFT_CNTL_MASK;
	if (!(reg_val & DOWNSHIFT_EN))
		*count = DOWNSHIFT_DEV_DISABLE;
	else
		*count = ((reg_val & ~DOWNSHIFT_EN) >> DOWNSHIFT_CNTL_POS) + 2;
	rc = vsc85xx_phy_page_set(phydev, MSCC_PHY_PAGE_STANDARD);

out:
	return rc;
}