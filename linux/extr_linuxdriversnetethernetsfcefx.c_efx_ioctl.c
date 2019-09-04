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
struct net_device {int dummy; } ;
struct mii_ioctl_data {int phy_id; } ;
struct ifreq {int dummy; } ;
struct efx_nic {int /*<<< orphan*/  mdio; } ;

/* Variables and functions */
 int MDIO_PHY_ID_C45 ; 
 int SIOCGHWTSTAMP ; 
 int SIOCGMIIREG ; 
 int SIOCSHWTSTAMP ; 
 int SIOCSMIIREG ; 
 int efx_ptp_get_ts_config (struct efx_nic*,struct ifreq*) ; 
 int efx_ptp_set_ts_config (struct efx_nic*,struct ifreq*) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int mdio_mii_ioctl (int /*<<< orphan*/ *,struct mii_ioctl_data*,int) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int efx_ioctl(struct net_device *net_dev, struct ifreq *ifr, int cmd)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	struct mii_ioctl_data *data = if_mii(ifr);

	if (cmd == SIOCSHWTSTAMP)
		return efx_ptp_set_ts_config(efx, ifr);
	if (cmd == SIOCGHWTSTAMP)
		return efx_ptp_get_ts_config(efx, ifr);

	/* Convert phy_id from older PRTAD/DEVAD format */
	if ((cmd == SIOCGMIIREG || cmd == SIOCSMIIREG) &&
	    (data->phy_id & 0xfc00) == 0x0400)
		data->phy_id ^= MDIO_PHY_ID_C45 | 0x0400;

	return mdio_mii_ioctl(&efx->mdio, data, cmd);
}