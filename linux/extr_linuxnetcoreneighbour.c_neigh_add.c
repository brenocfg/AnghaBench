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
struct pneigh_entry {int flags; } ;
struct nlmsghdr {int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int addr_len; } ;
struct net {int dummy; } ;
struct neighbour {int dummy; } ;
struct neigh_table {scalar_t__ key_len; } ;
struct ndmsg {int ndm_flags; int /*<<< orphan*/  ndm_state; int /*<<< orphan*/  ndm_family; scalar_t__ ndm_ifindex; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EAFNOSUPPORT ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENODEV ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct neighbour*) ; 
 size_t NDA_DST ; 
 size_t NDA_LLADDR ; 
 int /*<<< orphan*/  NDA_MAX ; 
 int NEIGH_UPDATE_F_ADMIN ; 
 int NEIGH_UPDATE_F_EXT_LEARNED ; 
 int NEIGH_UPDATE_F_OVERRIDE ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int NLM_F_CREATE ; 
 int NLM_F_EXCL ; 
 int NLM_F_REPLACE ; 
 int NTF_EXT_LEARNED ; 
 int NTF_PROXY ; 
 int NTF_USE ; 
 int PTR_ERR (struct neighbour*) ; 
 struct net_device* __dev_get_by_index (struct net*,scalar_t__) ; 
 struct neighbour* __neigh_lookup_errno (struct neigh_table*,void*,struct net_device*) ; 
 int /*<<< orphan*/  neigh_event_send (struct neighbour*,int /*<<< orphan*/ *) ; 
 struct neigh_table* neigh_find_table (int /*<<< orphan*/ ) ; 
 struct neighbour* neigh_lookup (struct neigh_table*,void*,struct net_device*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int neigh_update (struct neighbour*,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 struct ndmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 struct pneigh_entry* pneigh_lookup (struct neigh_table*,struct net*,void*,struct net_device*,int) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int neigh_add(struct sk_buff *skb, struct nlmsghdr *nlh,
		     struct netlink_ext_ack *extack)
{
	int flags = NEIGH_UPDATE_F_ADMIN | NEIGH_UPDATE_F_OVERRIDE;
	struct net *net = sock_net(skb->sk);
	struct ndmsg *ndm;
	struct nlattr *tb[NDA_MAX+1];
	struct neigh_table *tbl;
	struct net_device *dev = NULL;
	struct neighbour *neigh;
	void *dst, *lladdr;
	int err;

	ASSERT_RTNL();
	err = nlmsg_parse(nlh, sizeof(*ndm), tb, NDA_MAX, NULL, extack);
	if (err < 0)
		goto out;

	err = -EINVAL;
	if (tb[NDA_DST] == NULL)
		goto out;

	ndm = nlmsg_data(nlh);
	if (ndm->ndm_ifindex) {
		dev = __dev_get_by_index(net, ndm->ndm_ifindex);
		if (dev == NULL) {
			err = -ENODEV;
			goto out;
		}

		if (tb[NDA_LLADDR] && nla_len(tb[NDA_LLADDR]) < dev->addr_len)
			goto out;
	}

	tbl = neigh_find_table(ndm->ndm_family);
	if (tbl == NULL)
		return -EAFNOSUPPORT;

	if (nla_len(tb[NDA_DST]) < (int)tbl->key_len)
		goto out;
	dst = nla_data(tb[NDA_DST]);
	lladdr = tb[NDA_LLADDR] ? nla_data(tb[NDA_LLADDR]) : NULL;

	if (ndm->ndm_flags & NTF_PROXY) {
		struct pneigh_entry *pn;

		err = -ENOBUFS;
		pn = pneigh_lookup(tbl, net, dst, dev, 1);
		if (pn) {
			pn->flags = ndm->ndm_flags;
			err = 0;
		}
		goto out;
	}

	if (dev == NULL)
		goto out;

	neigh = neigh_lookup(tbl, dst, dev);
	if (neigh == NULL) {
		if (!(nlh->nlmsg_flags & NLM_F_CREATE)) {
			err = -ENOENT;
			goto out;
		}

		neigh = __neigh_lookup_errno(tbl, dst, dev);
		if (IS_ERR(neigh)) {
			err = PTR_ERR(neigh);
			goto out;
		}
	} else {
		if (nlh->nlmsg_flags & NLM_F_EXCL) {
			err = -EEXIST;
			neigh_release(neigh);
			goto out;
		}

		if (!(nlh->nlmsg_flags & NLM_F_REPLACE))
			flags &= ~NEIGH_UPDATE_F_OVERRIDE;
	}

	if (ndm->ndm_flags & NTF_EXT_LEARNED)
		flags |= NEIGH_UPDATE_F_EXT_LEARNED;

	if (ndm->ndm_flags & NTF_USE) {
		neigh_event_send(neigh, NULL);
		err = 0;
	} else
		err = neigh_update(neigh, lladdr, ndm->ndm_state, flags,
				   NETLINK_CB(skb).portid);
	neigh_release(neigh);

out:
	return err;
}