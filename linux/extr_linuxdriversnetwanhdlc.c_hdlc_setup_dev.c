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
struct net_device {int flags; int min_mtu; int hard_header_len; int /*<<< orphan*/ * header_ops; scalar_t__ addr_len; int /*<<< orphan*/  type; void* max_mtu; void* mtu; int /*<<< orphan*/  priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_RAWHDLC ; 
 void* HDLC_MAX_MTU ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  IFF_WAN_HDLC ; 
 int /*<<< orphan*/  hdlc_null_ops ; 

__attribute__((used)) static void hdlc_setup_dev(struct net_device *dev)
{
	/* Re-init all variables changed by HDLC protocol drivers,
	 * including ether_setup() called from hdlc_raw_eth.c.
	 */
	dev->flags		 = IFF_POINTOPOINT | IFF_NOARP;
	dev->priv_flags		 = IFF_WAN_HDLC;
	dev->mtu		 = HDLC_MAX_MTU;
	dev->min_mtu		 = 68;
	dev->max_mtu		 = HDLC_MAX_MTU;
	dev->type		 = ARPHRD_RAWHDLC;
	dev->hard_header_len	 = 16;
	dev->addr_len		 = 0;
	dev->header_ops		 = &hdlc_null_ops;
}