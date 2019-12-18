#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct hsr_priv {int /*<<< orphan*/  sequence_nr; int /*<<< orphan*/  sup_multicast_addr; } ;
struct hsr_port {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HSR_PT_SLAVE_A ; 
 int /*<<< orphan*/  HSR_PT_SLAVE_B ; 
 int /*<<< orphan*/  IFLA_HSR_SEQ_NR ; 
 int /*<<< orphan*/  IFLA_HSR_SLAVE1 ; 
 int /*<<< orphan*/  IFLA_HSR_SLAVE2 ; 
 int /*<<< orphan*/  IFLA_HSR_SUPERVISION_ADDR ; 
 struct hsr_port* hsr_port_get_hsr (struct hsr_priv*,int /*<<< orphan*/ ) ; 
 struct hsr_priv* netdev_priv (struct net_device const*) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int hsr_fill_info(struct sk_buff *skb, const struct net_device *dev)
{
	struct hsr_priv *hsr;
	struct hsr_port *port;
	int res;

	hsr = netdev_priv(dev);

	res = 0;

	rcu_read_lock();
	port = hsr_port_get_hsr(hsr, HSR_PT_SLAVE_A);
	if (port)
		res = nla_put_u32(skb, IFLA_HSR_SLAVE1, port->dev->ifindex);
	rcu_read_unlock();
	if (res)
		goto nla_put_failure;

	rcu_read_lock();
	port = hsr_port_get_hsr(hsr, HSR_PT_SLAVE_B);
	if (port)
		res = nla_put_u32(skb, IFLA_HSR_SLAVE2, port->dev->ifindex);
	rcu_read_unlock();
	if (res)
		goto nla_put_failure;

	if (nla_put(skb, IFLA_HSR_SUPERVISION_ADDR, ETH_ALEN,
		    hsr->sup_multicast_addr) ||
	    nla_put_u16(skb, IFLA_HSR_SEQ_NR, hsr->sequence_nr))
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}