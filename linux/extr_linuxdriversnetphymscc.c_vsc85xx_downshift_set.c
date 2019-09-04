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
 int DOWNSHIFT_COUNT_MAX ; 
 int DOWNSHIFT_DEV_DEFAULT_COUNT ; 
 int DOWNSHIFT_EN ; 
 int ERANGE ; 
 int /*<<< orphan*/  MSCC_PHY_ACTIPHY_CNTL ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_EXTENDED ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_STANDARD ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phydev_err (struct phy_device*,char*) ; 
 int vsc85xx_phy_page_set (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsc85xx_downshift_set(struct phy_device *phydev, u8 count)
{
	int rc;
	u16 reg_val;

	if (count == DOWNSHIFT_DEV_DEFAULT_COUNT) {
		/* Default downshift count 3 (i.e. Bit3:2 = 0b01) */
		count = ((1 << DOWNSHIFT_CNTL_POS) | DOWNSHIFT_EN);
	} else if (count > DOWNSHIFT_COUNT_MAX || count == 1) {
		phydev_err(phydev, "Downshift count should be 2,3,4 or 5\n");
		return -ERANGE;
	} else if (count) {
		/* Downshift count is either 2,3,4 or 5 */
		count = (((count - 2) << DOWNSHIFT_CNTL_POS) | DOWNSHIFT_EN);
	}

	rc = vsc85xx_phy_page_set(phydev, MSCC_PHY_PAGE_EXTENDED);
	if (rc != 0)
		goto out;

	reg_val = phy_read(phydev, MSCC_PHY_ACTIPHY_CNTL);
	reg_val &= ~(DOWNSHIFT_CNTL_MASK);
	reg_val |= count;
	rc = phy_write(phydev, MSCC_PHY_ACTIPHY_CNTL, reg_val);
	if (rc != 0)
		goto out;

	rc = vsc85xx_phy_page_set(phydev, MSCC_PHY_PAGE_STANDARD);

out:
	return rc;
}