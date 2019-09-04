#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ en; } ;
union cvmx_gmxx_prtx_cfg {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
struct octeon_ethernet {int /*<<< orphan*/  port; scalar_t__ last_link; int /*<<< orphan*/ * poll; } ;
struct net_device {scalar_t__ phydev; } ;
struct TYPE_6__ {scalar_t__ u64; } ;
typedef  TYPE_2__ cvmx_helper_link_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_PRTX_CFG (int,int) ; 
 int INDEX (int /*<<< orphan*/ ) ; 
 int INTERFACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvm_oct_note_carrier (struct octeon_ethernet*,TYPE_2__) ; 
 int /*<<< orphan*/  cvmx_helper_link_set (int /*<<< orphan*/ ,TYPE_2__) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 

int cvm_oct_common_stop(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);
	int interface = INTERFACE(priv->port);
	cvmx_helper_link_info_t link_info;
	union cvmx_gmxx_prtx_cfg gmx_cfg;
	int index = INDEX(priv->port);

	gmx_cfg.u64 = cvmx_read_csr(CVMX_GMXX_PRTX_CFG(index, interface));
	gmx_cfg.s.en = 0;
	cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface), gmx_cfg.u64);

	priv->poll = NULL;

	if (dev->phydev)
		phy_disconnect(dev->phydev);

	if (priv->last_link) {
		link_info.u64 = 0;
		priv->last_link = 0;

		cvmx_helper_link_set(priv->port, link_info);
		cvm_oct_note_carrier(priv, link_info);
	}
	return 0;
}