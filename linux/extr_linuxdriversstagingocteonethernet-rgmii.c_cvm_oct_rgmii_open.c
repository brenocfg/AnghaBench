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
struct octeon_ethernet {scalar_t__ imode; scalar_t__ port; int /*<<< orphan*/  (* poll ) (struct net_device*) ;} ;
struct net_device {scalar_t__ phydev; } ;

/* Variables and functions */
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_GMII ; 
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_RGMII ; 
 int /*<<< orphan*/  cvm_oct_check_preamble_errors (struct net_device*) ; 
 int cvm_oct_common_open (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvm_oct_rgmii_poll ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 

int cvm_oct_rgmii_open(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);
	int ret;

	ret = cvm_oct_common_open(dev, cvm_oct_rgmii_poll);
	if (ret)
		return ret;

	if (dev->phydev) {
		/*
		 * In phydev mode, we need still periodic polling for the
		 * preamble error checking, and we also need to call this
		 * function on every link state change.
		 *
		 * Only true RGMII ports need to be polled. In GMII mode, port
		 * 0 is really a RGMII port.
		 */
		if ((priv->imode == CVMX_HELPER_INTERFACE_MODE_GMII &&
		     priv->port  == 0) ||
		    (priv->imode == CVMX_HELPER_INTERFACE_MODE_RGMII)) {
			priv->poll = cvm_oct_check_preamble_errors;
			cvm_oct_check_preamble_errors(dev);
		}
	}

	return 0;
}