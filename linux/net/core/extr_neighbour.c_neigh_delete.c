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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct neighbour {int dummy; } ;
struct neigh_table {int /*<<< orphan*/  lock; scalar_t__ key_len; } ;
struct ndmsg {int ndm_flags; int /*<<< orphan*/  ndm_family; scalar_t__ ndm_ifindex; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int /*<<< orphan*/  NDA_DST ; 
 int NEIGH_UPDATE_F_ADMIN ; 
 int NEIGH_UPDATE_F_OVERRIDE ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int NTF_PROXY ; 
 int /*<<< orphan*/  NUD_FAILED ; 
 struct net_device* __dev_get_by_index (struct net*,scalar_t__) ; 
 int __neigh_update (struct neighbour*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct neigh_table* neigh_find_table (int /*<<< orphan*/ ) ; 
 struct neighbour* neigh_lookup (struct neigh_table*,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_remove_one (struct neighbour*,struct neigh_table*) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 struct ndmsg* nlmsg_data (struct nlmsghdr*) ; 
 struct nlattr* nlmsg_find_attr (struct nlmsghdr*,int,int /*<<< orphan*/ ) ; 
 int nlmsg_len (struct nlmsghdr*) ; 
 int pneigh_delete (struct neigh_table*,struct net*,int /*<<< orphan*/ ,struct net_device*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int neigh_delete(struct sk_buff *skb, struct nlmsghdr *nlh,
			struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct ndmsg *ndm;
	struct nlattr *dst_attr;
	struct neigh_table *tbl;
	struct neighbour *neigh;
	struct net_device *dev = NULL;
	int err = -EINVAL;

	ASSERT_RTNL();
	if (nlmsg_len(nlh) < sizeof(*ndm))
		goto out;

	dst_attr = nlmsg_find_attr(nlh, sizeof(*ndm), NDA_DST);
	if (!dst_attr) {
		NL_SET_ERR_MSG(extack, "Network address not specified");
		goto out;
	}

	ndm = nlmsg_data(nlh);
	if (ndm->ndm_ifindex) {
		dev = __dev_get_by_index(net, ndm->ndm_ifindex);
		if (dev == NULL) {
			err = -ENODEV;
			goto out;
		}
	}

	tbl = neigh_find_table(ndm->ndm_family);
	if (tbl == NULL)
		return -EAFNOSUPPORT;

	if (nla_len(dst_attr) < (int)tbl->key_len) {
		NL_SET_ERR_MSG(extack, "Invalid network address");
		goto out;
	}

	if (ndm->ndm_flags & NTF_PROXY) {
		err = pneigh_delete(tbl, net, nla_data(dst_attr), dev);
		goto out;
	}

	if (dev == NULL)
		goto out;

	neigh = neigh_lookup(tbl, nla_data(dst_attr), dev);
	if (neigh == NULL) {
		err = -ENOENT;
		goto out;
	}

	err = __neigh_update(neigh, NULL, NUD_FAILED,
			     NEIGH_UPDATE_F_OVERRIDE | NEIGH_UPDATE_F_ADMIN,
			     NETLINK_CB(skb).portid, extack);
	write_lock_bh(&tbl->lock);
	neigh_release(neigh);
	neigh_remove_one(neigh, tbl);
	write_unlock_bh(&tbl->lock);

out:
	return err;
}