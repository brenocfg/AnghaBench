#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct net_device {unsigned int base_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  supported; } ;
struct TYPE_3__ {int /*<<< orphan*/  duplex; scalar_t__ phy_address; int /*<<< orphan*/  speed; int /*<<< orphan*/  port; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;

/* Variables and functions */
 int CFG_AUI_SELECT ; 
 scalar_t__ CONFIG ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 scalar_t__ MGMT ; 
 int /*<<< orphan*/  PORT_AUI ; 
 int /*<<< orphan*/  PORT_TP ; 
 int /*<<< orphan*/  SMC_SELECT_BANK (int) ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_AUI ; 
 int SUPPORTED_TP ; 
 scalar_t__ TCR ; 
 int TCR_FDUPLX ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 int inw (scalar_t__) ; 

__attribute__((used)) static void smc_netdev_get_ecmd(struct net_device *dev,
				struct ethtool_link_ksettings *ecmd)
{
	u16 tmp;
	unsigned int ioaddr = dev->base_addr;
	u32 supported;

	supported = (SUPPORTED_TP | SUPPORTED_AUI |
		     SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full);

	SMC_SELECT_BANK(1);
	tmp = inw(ioaddr + CONFIG);
	ecmd->base.port = (tmp & CFG_AUI_SELECT) ? PORT_AUI : PORT_TP;
	ecmd->base.speed = SPEED_10;
	ecmd->base.phy_address = ioaddr + MGMT;

	SMC_SELECT_BANK(0);
	tmp = inw(ioaddr + TCR);
	ecmd->base.duplex = (tmp & TCR_FDUPLX) ? DUPLEX_FULL : DUPLEX_HALF;

	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.supported,
						supported);
}