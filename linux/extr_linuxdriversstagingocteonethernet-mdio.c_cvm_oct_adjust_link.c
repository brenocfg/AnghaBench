#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct octeon_ethernet {scalar_t__ last_link; int /*<<< orphan*/  port; int /*<<< orphan*/  (* poll ) (struct net_device*) ;scalar_t__ link_info; } ;
struct net_device {TYPE_2__* phydev; } ;
struct TYPE_6__ {int link_up; int full_duplex; int /*<<< orphan*/  speed; } ;
struct TYPE_8__ {scalar_t__ u64; TYPE_1__ s; } ;
typedef  TYPE_3__ cvmx_helper_link_info_t ;
struct TYPE_7__ {scalar_t__ link; int /*<<< orphan*/  speed; scalar_t__ duplex; } ;

/* Variables and functions */
 int /*<<< orphan*/  cvm_oct_note_carrier (struct octeon_ethernet*,TYPE_3__) ; 
 int /*<<< orphan*/  cvmx_helper_link_set (int /*<<< orphan*/ ,TYPE_3__) ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

void cvm_oct_adjust_link(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);
	cvmx_helper_link_info_t link_info;

	link_info.u64		= 0;
	link_info.s.link_up	= dev->phydev->link ? 1 : 0;
	link_info.s.full_duplex = dev->phydev->duplex ? 1 : 0;
	link_info.s.speed	= dev->phydev->speed;
	priv->link_info		= link_info.u64;

	/*
	 * The polling task need to know about link status changes.
	 */
	if (priv->poll)
		priv->poll(dev);

	if (priv->last_link != dev->phydev->link) {
		priv->last_link = dev->phydev->link;
		cvmx_helper_link_set(priv->port, link_info);
		cvm_oct_note_carrier(priv, link_info);
	}
}