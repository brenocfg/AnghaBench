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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct hostap_interface {TYPE_2__* local; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {TYPE_1__* func; } ;
struct TYPE_3__ {int (* set_rid ) (struct net_device*,int,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 int stub1 (struct net_device*,int,int /*<<< orphan*/ *,int) ; 

int hostap_set_word(struct net_device *dev, int rid, u16 val)
{
	struct hostap_interface *iface;
	__le16 tmp = cpu_to_le16(val);
	iface = netdev_priv(dev);
	return iface->local->func->set_rid(dev, rid, &tmp, 2);
}