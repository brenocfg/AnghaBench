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
struct net_device {int dummy; } ;
struct fc_lport {int link_supported_speeds; int /*<<< orphan*/  link_speed; } ;
struct TYPE_4__ {int /*<<< orphan*/  speed; } ;
struct TYPE_3__ {int* supported; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;

/* Variables and functions */
 int FC_PORTSPEED_10GBIT ; 
 int FC_PORTSPEED_1GBIT ; 
 int FC_PORTSPEED_20GBIT ; 
 int FC_PORTSPEED_40GBIT ; 
 int SUPPORTED_10000baseKR_Full ; 
 int SUPPORTED_10000baseKX4_Full ; 
 int SUPPORTED_10000baseR_FEC ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_1000baseKX_Full ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_20000baseKR2_Full ; 
 int SUPPORTED_20000baseMLD2_Full ; 
 int SUPPORTED_40000baseCR4_Full ; 
 int SUPPORTED_40000baseKR4_Full ; 
 int SUPPORTED_40000baseLR4_Full ; 
 int SUPPORTED_40000baseSR4_Full ; 
 int /*<<< orphan*/  __ethtool_get_link_ksettings (struct net_device*,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  eth2fc_speed (int /*<<< orphan*/ ) ; 
 struct net_device* fcoe_get_netdev (struct fc_lport*) ; 

int fcoe_link_speed_update(struct fc_lport *lport)
{
	struct net_device *netdev = fcoe_get_netdev(lport);
	struct ethtool_link_ksettings ecmd;

	if (!__ethtool_get_link_ksettings(netdev, &ecmd)) {
		lport->link_supported_speeds &= ~(FC_PORTSPEED_1GBIT  |
		                                  FC_PORTSPEED_10GBIT |
		                                  FC_PORTSPEED_20GBIT |
		                                  FC_PORTSPEED_40GBIT);

		if (ecmd.link_modes.supported[0] & (
			    SUPPORTED_1000baseT_Half |
			    SUPPORTED_1000baseT_Full |
			    SUPPORTED_1000baseKX_Full))
			lport->link_supported_speeds |= FC_PORTSPEED_1GBIT;

		if (ecmd.link_modes.supported[0] & (
			    SUPPORTED_10000baseT_Full   |
			    SUPPORTED_10000baseKX4_Full |
			    SUPPORTED_10000baseKR_Full  |
			    SUPPORTED_10000baseR_FEC))
			lport->link_supported_speeds |= FC_PORTSPEED_10GBIT;

		if (ecmd.link_modes.supported[0] & (
			    SUPPORTED_20000baseMLD2_Full |
			    SUPPORTED_20000baseKR2_Full))
			lport->link_supported_speeds |= FC_PORTSPEED_20GBIT;

		if (ecmd.link_modes.supported[0] & (
			    SUPPORTED_40000baseKR4_Full |
			    SUPPORTED_40000baseCR4_Full |
			    SUPPORTED_40000baseSR4_Full |
			    SUPPORTED_40000baseLR4_Full))
			lport->link_supported_speeds |= FC_PORTSPEED_40GBIT;

		lport->link_speed = eth2fc_speed(ecmd.base.speed);
		return 0;
	}
	return -1;
}