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
struct phy_device {int dummy; } ;
struct net_device {struct phy_device* phydev; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  SIOCGHWTSTAMP 129 
#define  SIOCSHWTSTAMP 128 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int phy_mii_ioctl (struct phy_device*,struct ifreq*,int) ; 
 int ravb_hwtstamp_get (struct net_device*,struct ifreq*) ; 
 int ravb_hwtstamp_set (struct net_device*,struct ifreq*) ; 

__attribute__((used)) static int ravb_do_ioctl(struct net_device *ndev, struct ifreq *req, int cmd)
{
	struct phy_device *phydev = ndev->phydev;

	if (!netif_running(ndev))
		return -EINVAL;

	if (!phydev)
		return -ENODEV;

	switch (cmd) {
	case SIOCGHWTSTAMP:
		return ravb_hwtstamp_get(ndev, req);
	case SIOCSHWTSTAMP:
		return ravb_hwtstamp_set(ndev, req);
	}

	return phy_mii_ioctl(phydev, req, cmd);
}