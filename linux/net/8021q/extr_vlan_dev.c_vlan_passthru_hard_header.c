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
struct vlan_dev_priv {struct net_device* real_dev; } ;
struct sk_buff {int dummy; } ;
struct net_device {void* dev_addr; } ;

/* Variables and functions */
 int dev_hard_header (struct sk_buff*,struct net_device*,unsigned short,void const*,void const*,unsigned int) ; 
 struct vlan_dev_priv* vlan_dev_priv (struct net_device*) ; 

__attribute__((used)) static int vlan_passthru_hard_header(struct sk_buff *skb, struct net_device *dev,
				     unsigned short type,
				     const void *daddr, const void *saddr,
				     unsigned int len)
{
	struct vlan_dev_priv *vlan = vlan_dev_priv(dev);
	struct net_device *real_dev = vlan->real_dev;

	if (saddr == NULL)
		saddr = dev->dev_addr;

	return dev_hard_header(skb, real_dev, type, daddr, saddr, len);
}