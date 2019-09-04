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
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Backplane_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_FIBRE_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Pause_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_TP_BIT ; 
#define  MC_CMD_MEDIA_BASE_T 132 
#define  MC_CMD_MEDIA_KX4 131 
#define  MC_CMD_MEDIA_QSFP_PLUS 130 
#define  MC_CMD_MEDIA_SFP_PLUS 129 
#define  MC_CMD_MEDIA_XFP 128 
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
 int /*<<< orphan*/  __ETHTOOL_LINK_MODE_MASK_NBITS ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  bitmap_zero (unsigned long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcdi_to_ethtool_linkset(u32 media, u32 cap, unsigned long *linkset)
{
	#define SET_BIT(name)	__set_bit(ETHTOOL_LINK_MODE_ ## name ## _BIT, \
					  linkset)

	bitmap_zero(linkset, __ETHTOOL_LINK_MODE_MASK_NBITS);
	switch (media) {
	case MC_CMD_MEDIA_KX4:
		SET_BIT(Backplane);
		if (cap & (1 << MC_CMD_PHY_CAP_1000FDX_LBN))
			SET_BIT(1000baseKX_Full);
		if (cap & (1 << MC_CMD_PHY_CAP_10000FDX_LBN))
			SET_BIT(10000baseKX4_Full);
		if (cap & (1 << MC_CMD_PHY_CAP_40000FDX_LBN))
			SET_BIT(40000baseKR4_Full);
		break;

	case MC_CMD_MEDIA_XFP:
	case MC_CMD_MEDIA_SFP_PLUS:
	case MC_CMD_MEDIA_QSFP_PLUS:
		SET_BIT(FIBRE);
		if (cap & (1 << MC_CMD_PHY_CAP_1000FDX_LBN))
			SET_BIT(1000baseT_Full);
		if (cap & (1 << MC_CMD_PHY_CAP_10000FDX_LBN))
			SET_BIT(10000baseT_Full);
		if (cap & (1 << MC_CMD_PHY_CAP_40000FDX_LBN))
			SET_BIT(40000baseCR4_Full);
		if (cap & (1 << MC_CMD_PHY_CAP_100000FDX_LBN))
			SET_BIT(100000baseCR4_Full);
		if (cap & (1 << MC_CMD_PHY_CAP_25000FDX_LBN))
			SET_BIT(25000baseCR_Full);
		if (cap & (1 << MC_CMD_PHY_CAP_50000FDX_LBN))
			SET_BIT(50000baseCR2_Full);
		break;

	case MC_CMD_MEDIA_BASE_T:
		SET_BIT(TP);
		if (cap & (1 << MC_CMD_PHY_CAP_10HDX_LBN))
			SET_BIT(10baseT_Half);
		if (cap & (1 << MC_CMD_PHY_CAP_10FDX_LBN))
			SET_BIT(10baseT_Full);
		if (cap & (1 << MC_CMD_PHY_CAP_100HDX_LBN))
			SET_BIT(100baseT_Half);
		if (cap & (1 << MC_CMD_PHY_CAP_100FDX_LBN))
			SET_BIT(100baseT_Full);
		if (cap & (1 << MC_CMD_PHY_CAP_1000HDX_LBN))
			SET_BIT(1000baseT_Half);
		if (cap & (1 << MC_CMD_PHY_CAP_1000FDX_LBN))
			SET_BIT(1000baseT_Full);
		if (cap & (1 << MC_CMD_PHY_CAP_10000FDX_LBN))
			SET_BIT(10000baseT_Full);
		break;
	}

	if (cap & (1 << MC_CMD_PHY_CAP_PAUSE_LBN))
		SET_BIT(Pause);
	if (cap & (1 << MC_CMD_PHY_CAP_ASYM_LBN))
		SET_BIT(Asym_Pause);
	if (cap & (1 << MC_CMD_PHY_CAP_AN_LBN))
		SET_BIT(Autoneg);

	#undef SET_BIT
}