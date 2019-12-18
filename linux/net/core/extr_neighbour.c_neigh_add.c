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
typedef  void* u8 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct pneigh_entry {int flags; void* protocol; } ;
struct nlmsghdr {int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int addr_len; } ;
struct net {int dummy; } ;
struct neighbour {void* protocol; } ;
struct neigh_table {int /*<<< orphan*/  (* allow_add ) (struct net_device*,struct netlink_ext_ack*) ;scalar_t__ key_len; } ;
struct ndmsg {int ndm_flags; int ndm_state; int /*<<< orphan*/  ndm_family; scalar_t__ ndm_ifindex; } ;
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
 size_t NDA_PROTOCOL ; 
 int NEIGH_UPDATE_F_ADMIN ; 
 int NEIGH_UPDATE_F_EXT_LEARNED ; 
 int NEIGH_UPDATE_F_ISROUTER ; 
 int NEIGH_UPDATE_F_OVERRIDE ; 
 int NEIGH_UPDATE_F_OVERRIDE_ISROUTER ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int NLM_F_CREATE ; 
 int NLM_F_EXCL ; 
 int NLM_F_REPLACE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int NTF_EXT_LEARNED ; 
 int NTF_PROXY ; 
 int NTF_ROUTER ; 
 int NTF_USE ; 
 int NUD_PERMANENT ; 
 int PTR_ERR (struct neighbour*) ; 
 struct neighbour* ___neigh_create (struct neigh_table*,void*,struct net_device*,int,int) ; 
 struct net_device* __dev_get_by_index (struct net*,scalar_t__) ; 
 int __neigh_update (struct neighbour*,void*,int,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  nda_policy ; 
 int /*<<< orphan*/  neigh_event_send (struct neighbour*,int /*<<< orphan*/ *) ; 
 struct neigh_table* neigh_find_table (int /*<<< orphan*/ ) ; 
 struct neighbour* neigh_lookup (struct neigh_table*,void*,struct net_device*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/ * nla_data (struct nlattr*) ; 
 void* nla_get_u8 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 struct ndmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct pneigh_entry* pneigh_lookup (struct neigh_table*,struct net*,void*,struct net_device*,int) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int neigh_add(struct sk_buff *skb, struct nlmsghdr *nlh,
		     struct netlink_ext_ack *extack)
{
	int flags = NEIGH_UPDATE_F_ADMIN | NEIGH_UPDATE_F_OVERRIDE |
		NEIGH_UPDATE_F_OVERRIDE_ISROUTER;
	struct net *net = sock_net(skb->sk);
	struct ndmsg *ndm;
	struct nlattr *tb[NDA_MAX+1];
	struct neigh_table *tbl;
	struct net_device *dev = NULL;
	struct neighbour *neigh;
	void *dst, *lladdr;
	u8 protocol = 0;
	int err;

	ASSERT_RTNL();
	err = nlmsg_parse_deprecated(nlh, sizeof(*ndm), tb, NDA_MAX,
				     nda_policy, extack);
	if (err < 0)
		goto out;

	err = -EINVAL;
	if (!tb[NDA_DST]) {
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

		if (tb[NDA_LLADDR] && nla_len(tb[NDA_LLADDR]) < dev->addr_len) {
			NL_SET_ERR_MSG(extack, "Invalid link address");
			goto out;
		}
	}

	tbl = neigh_find_table(ndm->ndm_family);
	if (tbl == NULL)
		return -EAFNOSUPPORT;

	if (nla_len(tb[NDA_DST]) < (int)tbl->key_len) {
		NL_SET_ERR_MSG(extack, "Invalid network address");
		goto out;
	}

	dst = nla_data(tb[NDA_DST]);
	lladdr = tb[NDA_LLADDR] ? nla_data(tb[NDA_LLADDR]) : NULL;

	if (tb[NDA_PROTOCOL])
		protocol = nla_get_u8(tb[NDA_PROTOCOL]);

	if (ndm->ndm_flags & NTF_PROXY) {
		struct pneigh_entry *pn;

		err = -ENOBUFS;
		pn = pneigh_lookup(tbl, net, dst, dev, 1);
		if (pn) {
			pn->flags = ndm->ndm_flags;
			if (protocol)
				pn->protocol = protocol;
			err = 0;
		}
		goto out;
	}

	if (!dev) {
		NL_SET_ERR_MSG(extack, "Device not specified");
		goto out;
	}

	if (tbl->allow_add && !tbl->allow_add(dev, extack)) {
		err = -EINVAL;
		goto out;
	}

	neigh = neigh_lookup(tbl, dst, dev);
	if (neigh == NULL) {
		bool exempt_from_gc;

		if (!(nlh->nlmsg_flags & NLM_F_CREATE)) {
			err = -ENOENT;
			goto out;
		}

		exempt_from_gc = ndm->ndm_state & NUD_PERMANENT ||
				 ndm->ndm_flags & NTF_EXT_LEARNED;
		neigh = ___neigh_create(tbl, dst, dev, exempt_from_gc, true);
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
			flags &= ~(NEIGH_UPDATE_F_OVERRIDE |
				   NEIGH_UPDATE_F_OVERRIDE_ISROUTER);
	}

	if (ndm->ndm_flags & NTF_EXT_LEARNED)
		flags |= NEIGH_UPDATE_F_EXT_LEARNED;

	if (ndm->ndm_flags & NTF_ROUTER)
		flags |= NEIGH_UPDATE_F_ISROUTER;

	if (ndm->ndm_flags & NTF_USE) {
		neigh_event_send(neigh, NULL);
		err = 0;
	} else
		err = __neigh_update(neigh, lladdr, ndm->ndm_state, flags,
				     NETLINK_CB(skb).portid, extack);

	if (protocol)
		neigh->protocol = protocol;

	neigh_release(neigh);

out:
	return err;
}