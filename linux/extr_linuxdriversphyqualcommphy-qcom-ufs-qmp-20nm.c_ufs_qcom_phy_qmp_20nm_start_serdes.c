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
struct ufs_qcom_phy {scalar_t__ mmio; } ;

/* Variables and functions */
 int MASK_SERDES_START ; 
 int OFFSET_SERDES_START ; 
 scalar_t__ UFS_PHY_PHY_START ; 
 int /*<<< orphan*/  mb () ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static inline void ufs_qcom_phy_qmp_20nm_start_serdes(struct ufs_qcom_phy *phy)
{
	u32 tmp;

	tmp = readl_relaxed(phy->mmio + UFS_PHY_PHY_START);
	tmp &= ~MASK_SERDES_START;
	tmp |= (1 << OFFSET_SERDES_START);
	writel_relaxed(tmp, phy->mmio + UFS_PHY_PHY_START);
	mb();
}