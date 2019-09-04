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
typedef  scalar_t__ u32 ;
struct tegra_xusb {int dummy; } ;

/* Variables and functions */
 scalar_t__ CSB_PAGE_OFFSET (unsigned int) ; 
 scalar_t__ CSB_PAGE_SELECT (unsigned int) ; 
 scalar_t__ XUSB_CFG_ARU_C11_CSBRANGE ; 
 scalar_t__ XUSB_CFG_CSB_BASE_ADDR ; 
 int /*<<< orphan*/  fpci_writel (struct tegra_xusb*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void csb_writel(struct tegra_xusb *tegra, u32 value,
		       unsigned int offset)
{
	u32 page = CSB_PAGE_SELECT(offset);
	u32 ofs = CSB_PAGE_OFFSET(offset);

	fpci_writel(tegra, page, XUSB_CFG_ARU_C11_CSBRANGE);
	fpci_writel(tegra, value, XUSB_CFG_CSB_BASE_ADDR + ofs);
}