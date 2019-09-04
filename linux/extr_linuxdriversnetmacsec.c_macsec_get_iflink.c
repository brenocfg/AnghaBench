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
struct TYPE_4__ {TYPE_1__* real_dev; } ;
struct TYPE_3__ {int ifindex; } ;

/* Variables and functions */
 TYPE_2__* macsec_priv (struct net_device const*) ; 

__attribute__((used)) static int macsec_get_iflink(const struct net_device *dev)
{
	return macsec_priv(dev)->real_dev->ifindex;
}