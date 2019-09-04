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
struct sk_buff {int dummy; } ;
struct netlink_callback {int dummy; } ;
struct net_device {int dummy; } ;
struct dsa_slave_dump_ctx {int idx; struct netlink_callback* cb; struct sk_buff* skb; struct net_device* dev; } ;
struct dsa_port {int dummy; } ;

/* Variables and functions */
 int dsa_port_fdb_dump (struct dsa_port*,int /*<<< orphan*/ ,struct dsa_slave_dump_ctx*) ; 
 int /*<<< orphan*/  dsa_slave_port_fdb_do_dump ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 

__attribute__((used)) static int
dsa_slave_fdb_dump(struct sk_buff *skb, struct netlink_callback *cb,
		   struct net_device *dev, struct net_device *filter_dev,
		   int *idx)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	struct dsa_slave_dump_ctx dump = {
		.dev = dev,
		.skb = skb,
		.cb = cb,
		.idx = *idx,
	};
	int err;

	err = dsa_port_fdb_dump(dp, dsa_slave_port_fdb_do_dump, &dump);
	*idx = dump.idx;

	return err;
}