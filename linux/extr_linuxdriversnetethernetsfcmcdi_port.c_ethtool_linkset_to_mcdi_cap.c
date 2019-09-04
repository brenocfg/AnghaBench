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

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseKX_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Half_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100baseT_Half_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10baseT_Half_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_25000baseCR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Asym_Pause_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Autoneg_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Pause_BIT ; 
 int MC_CMD_PHY_CAP_100000FDX_LBN ; 
 int MC_CMD_PHY_CAP_10000FDX_LBN ; 
 int MC_CMD_PHY_CAP_1000FDX_LBN ; 
 int MC_CMD_PHY_CAP_1000HDX_LBN ; 
 int MC_CMD_PHY_CAP_100FDX_LBN ; 
 int MC_CMD_PHY_CAP_100HDX_LBN ; 
 int MC_CMD_PHY_CAP_10FDX_LBN ; 
 int MC_CMD_PHY_CAP_10HDX_LBN ; 
 int MC_CMD_PHY_CAP_25000FDX_LBN ; 
 int MC_CMD_PHY_CAP_40000FDX_LBN ; 
 int MC_CMD_PHY_CAP_50000FDX_LBN ; 
 int MC_CMD_PHY_CAP_AN_LBN ; 
 int MC_CMD_PHY_CAP_ASYM_LBN ; 
 int MC_CMD_PHY_CAP_PAUSE_LBN ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long const*) ; 

__attribute__((used)) static u32 ethtool_linkset_to_mcdi_cap(const unsigned long *linkset)
{
	u32 result = 0;

	#define TEST_BIT(name)	test_bit(ETHTOOL_LINK_MODE_ ## name ## _BIT, \
					 linkset)

	if (TEST_BIT(10baseT_Half))
		result |= (1 << MC_CMD_PHY_CAP_10HDX_LBN);
	if (TEST_BIT(10baseT_Full))
		result |= (1 << MC_CMD_PHY_CAP_10FDX_LBN);
	if (TEST_BIT(100baseT_Half))
		result |= (1 << MC_CMD_PHY_CAP_100HDX_LBN);
	if (TEST_BIT(100baseT_Full))
		result |= (1 << MC_CMD_PHY_CAP_100FDX_LBN);
	if (TEST_BIT(1000baseT_Half))
		result |= (1 << MC_CMD_PHY_CAP_1000HDX_LBN);
	if (TEST_BIT(1000baseT_Full) || TEST_BIT(1000baseKX_Full))
		result |= (1 << MC_CMD_PHY_CAP_1000FDX_LBN);
	if (TEST_BIT(10000baseT_Full) || TEST_BIT(10000baseKX4_Full))
		result |= (1 << MC_CMD_PHY_CAP_10000FDX_LBN);
	if (TEST_BIT(40000baseCR4_Full) || TEST_BIT(40000baseKR4_Full))
		result |= (1 << MC_CMD_PHY_CAP_40000FDX_LBN);
	if (TEST_BIT(100000baseCR4_Full))
		result |= (1 << MC_CMD_PHY_CAP_100000FDX_LBN);
	if (TEST_BIT(25000baseCR_Full))
		result |= (1 << MC_CMD_PHY_CAP_25000FDX_LBN);
	if (TEST_BIT(50000baseCR2_Full))
		result |= (1 << MC_CMD_PHY_CAP_50000FDX_LBN);
	if (TEST_BIT(Pause))
		result |= (1 << MC_CMD_PHY_CAP_PAUSE_LBN);
	if (TEST_BIT(Asym_Pause))
		result |= (1 << MC_CMD_PHY_CAP_ASYM_LBN);
	if (TEST_BIT(Autoneg))
		result |= (1 << MC_CMD_PHY_CAP_AN_LBN);

	#undef TEST_BIT

	return result;
}