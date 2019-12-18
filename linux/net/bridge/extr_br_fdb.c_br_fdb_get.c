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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net_bridge_fdb_entry {int dummy; } ;
struct net_bridge {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  RTM_NEWNEIGH ; 
 struct net_bridge_fdb_entry* br_fdb_find_rcu (struct net_bridge*,unsigned char const*,int /*<<< orphan*/ ) ; 
 int fdb_fill_info (struct sk_buff*,struct net_bridge*,struct net_bridge_fdb_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_bridge* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int br_fdb_get(struct sk_buff *skb,
	       struct nlattr *tb[],
	       struct net_device *dev,
	       const unsigned char *addr,
	       u16 vid, u32 portid, u32 seq,
	       struct netlink_ext_ack *extack)
{
	struct net_bridge *br = netdev_priv(dev);
	struct net_bridge_fdb_entry *f;
	int err = 0;

	rcu_read_lock();
	f = br_fdb_find_rcu(br, addr, vid);
	if (!f) {
		NL_SET_ERR_MSG(extack, "Fdb entry not found");
		err = -ENOENT;
		goto errout;
	}

	err = fdb_fill_info(skb, br, f, portid, seq,
			    RTM_NEWNEIGH, 0);
errout:
	rcu_read_unlock();
	return err;
}