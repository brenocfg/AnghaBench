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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct neigh_table {scalar_t__ family; int gc_thresh1; int gc_thresh2; int gc_thresh3; int gc_interval; int /*<<< orphan*/  lock; int /*<<< orphan*/  id; } ;
struct neigh_parms {int /*<<< orphan*/  reachable_time; } ;
struct ndtmsg {scalar_t__ ndtm_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANYCAST_DELAY ; 
 int /*<<< orphan*/  APP_PROBES ; 
 int /*<<< orphan*/  BASE_REACHABLE_TIME ; 
 int /*<<< orphan*/  DELAY_PROBE_TIME ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  ETH_FRAME_LEN ; 
 int /*<<< orphan*/  GC_STALETIME ; 
 int /*<<< orphan*/  LOCKTIME ; 
 int /*<<< orphan*/  MCAST_PROBES ; 
 int /*<<< orphan*/  MCAST_REPROBES ; 
 size_t NDTA_GC_INTERVAL ; 
 int /*<<< orphan*/  NDTA_MAX ; 
 size_t NDTA_NAME ; 
 size_t NDTA_PARMS ; 
 size_t NDTA_THRESH1 ; 
 size_t NDTA_THRESH2 ; 
 size_t NDTA_THRESH3 ; 
#define  NDTPA_ANYCAST_DELAY 141 
#define  NDTPA_APP_PROBES 140 
#define  NDTPA_BASE_REACHABLE_TIME 139 
#define  NDTPA_DELAY_PROBE_TIME 138 
#define  NDTPA_GC_STALETIME 137 
 size_t NDTPA_IFINDEX ; 
#define  NDTPA_LOCKTIME 136 
 int NDTPA_MAX ; 
#define  NDTPA_MCAST_PROBES 135 
#define  NDTPA_MCAST_REPROBES 134 
#define  NDTPA_PROXY_DELAY 133 
#define  NDTPA_PROXY_QLEN 132 
#define  NDTPA_QUEUE_LEN 131 
#define  NDTPA_QUEUE_LENBYTES 130 
#define  NDTPA_RETRANS_TIME 129 
#define  NDTPA_UCAST_PROBES 128 
 int NEIGH_NR_TABLES ; 
 int /*<<< orphan*/  NEIGH_VAR (struct neigh_parms*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEIGH_VAR_SET (struct neigh_parms*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NETEVENT_DELAY_PROBE_TIME_UPDATE ; 
 int /*<<< orphan*/  PROXY_DELAY ; 
 int /*<<< orphan*/  PROXY_QLEN ; 
 int /*<<< orphan*/  QUEUE_LEN_BYTES ; 
 int /*<<< orphan*/  RETRANS_TIME ; 
 int SKB_TRUESIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UCAST_PROBES ; 
 int /*<<< orphan*/  call_netevent_notifiers (int /*<<< orphan*/ ,struct neigh_parms*) ; 
 int /*<<< orphan*/  init_net ; 
 struct neigh_parms* lookup_neigh_parms (struct neigh_table*,struct net*,int) ; 
 int /*<<< orphan*/  neigh_rand_reach_time (int /*<<< orphan*/ ) ; 
 struct neigh_table** neigh_tables ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl_neightbl_policy ; 
 int /*<<< orphan*/  nl_ntbl_parm_policy ; 
 int nla_get_msecs (struct nlattr*) ; 
 int nla_get_u32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int,struct nlattr*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 scalar_t__ nla_strcmp (struct nlattr*,int /*<<< orphan*/ ) ; 
 struct ndtmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int neightbl_set(struct sk_buff *skb, struct nlmsghdr *nlh,
			struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct neigh_table *tbl;
	struct ndtmsg *ndtmsg;
	struct nlattr *tb[NDTA_MAX+1];
	bool found = false;
	int err, tidx;

	err = nlmsg_parse_deprecated(nlh, sizeof(*ndtmsg), tb, NDTA_MAX,
				     nl_neightbl_policy, extack);
	if (err < 0)
		goto errout;

	if (tb[NDTA_NAME] == NULL) {
		err = -EINVAL;
		goto errout;
	}

	ndtmsg = nlmsg_data(nlh);

	for (tidx = 0; tidx < NEIGH_NR_TABLES; tidx++) {
		tbl = neigh_tables[tidx];
		if (!tbl)
			continue;
		if (ndtmsg->ndtm_family && tbl->family != ndtmsg->ndtm_family)
			continue;
		if (nla_strcmp(tb[NDTA_NAME], tbl->id) == 0) {
			found = true;
			break;
		}
	}

	if (!found)
		return -ENOENT;

	/*
	 * We acquire tbl->lock to be nice to the periodic timers and
	 * make sure they always see a consistent set of values.
	 */
	write_lock_bh(&tbl->lock);

	if (tb[NDTA_PARMS]) {
		struct nlattr *tbp[NDTPA_MAX+1];
		struct neigh_parms *p;
		int i, ifindex = 0;

		err = nla_parse_nested_deprecated(tbp, NDTPA_MAX,
						  tb[NDTA_PARMS],
						  nl_ntbl_parm_policy, extack);
		if (err < 0)
			goto errout_tbl_lock;

		if (tbp[NDTPA_IFINDEX])
			ifindex = nla_get_u32(tbp[NDTPA_IFINDEX]);

		p = lookup_neigh_parms(tbl, net, ifindex);
		if (p == NULL) {
			err = -ENOENT;
			goto errout_tbl_lock;
		}

		for (i = 1; i <= NDTPA_MAX; i++) {
			if (tbp[i] == NULL)
				continue;

			switch (i) {
			case NDTPA_QUEUE_LEN:
				NEIGH_VAR_SET(p, QUEUE_LEN_BYTES,
					      nla_get_u32(tbp[i]) *
					      SKB_TRUESIZE(ETH_FRAME_LEN));
				break;
			case NDTPA_QUEUE_LENBYTES:
				NEIGH_VAR_SET(p, QUEUE_LEN_BYTES,
					      nla_get_u32(tbp[i]));
				break;
			case NDTPA_PROXY_QLEN:
				NEIGH_VAR_SET(p, PROXY_QLEN,
					      nla_get_u32(tbp[i]));
				break;
			case NDTPA_APP_PROBES:
				NEIGH_VAR_SET(p, APP_PROBES,
					      nla_get_u32(tbp[i]));
				break;
			case NDTPA_UCAST_PROBES:
				NEIGH_VAR_SET(p, UCAST_PROBES,
					      nla_get_u32(tbp[i]));
				break;
			case NDTPA_MCAST_PROBES:
				NEIGH_VAR_SET(p, MCAST_PROBES,
					      nla_get_u32(tbp[i]));
				break;
			case NDTPA_MCAST_REPROBES:
				NEIGH_VAR_SET(p, MCAST_REPROBES,
					      nla_get_u32(tbp[i]));
				break;
			case NDTPA_BASE_REACHABLE_TIME:
				NEIGH_VAR_SET(p, BASE_REACHABLE_TIME,
					      nla_get_msecs(tbp[i]));
				/* update reachable_time as well, otherwise, the change will
				 * only be effective after the next time neigh_periodic_work
				 * decides to recompute it (can be multiple minutes)
				 */
				p->reachable_time =
					neigh_rand_reach_time(NEIGH_VAR(p, BASE_REACHABLE_TIME));
				break;
			case NDTPA_GC_STALETIME:
				NEIGH_VAR_SET(p, GC_STALETIME,
					      nla_get_msecs(tbp[i]));
				break;
			case NDTPA_DELAY_PROBE_TIME:
				NEIGH_VAR_SET(p, DELAY_PROBE_TIME,
					      nla_get_msecs(tbp[i]));
				call_netevent_notifiers(NETEVENT_DELAY_PROBE_TIME_UPDATE, p);
				break;
			case NDTPA_RETRANS_TIME:
				NEIGH_VAR_SET(p, RETRANS_TIME,
					      nla_get_msecs(tbp[i]));
				break;
			case NDTPA_ANYCAST_DELAY:
				NEIGH_VAR_SET(p, ANYCAST_DELAY,
					      nla_get_msecs(tbp[i]));
				break;
			case NDTPA_PROXY_DELAY:
				NEIGH_VAR_SET(p, PROXY_DELAY,
					      nla_get_msecs(tbp[i]));
				break;
			case NDTPA_LOCKTIME:
				NEIGH_VAR_SET(p, LOCKTIME,
					      nla_get_msecs(tbp[i]));
				break;
			}
		}
	}

	err = -ENOENT;
	if ((tb[NDTA_THRESH1] || tb[NDTA_THRESH2] ||
	     tb[NDTA_THRESH3] || tb[NDTA_GC_INTERVAL]) &&
	    !net_eq(net, &init_net))
		goto errout_tbl_lock;

	if (tb[NDTA_THRESH1])
		tbl->gc_thresh1 = nla_get_u32(tb[NDTA_THRESH1]);

	if (tb[NDTA_THRESH2])
		tbl->gc_thresh2 = nla_get_u32(tb[NDTA_THRESH2]);

	if (tb[NDTA_THRESH3])
		tbl->gc_thresh3 = nla_get_u32(tb[NDTA_THRESH3]);

	if (tb[NDTA_GC_INTERVAL])
		tbl->gc_interval = nla_get_msecs(tb[NDTA_GC_INTERVAL]);

	err = 0;

errout_tbl_lock:
	write_unlock_bh(&tbl->lock);
errout:
	return err;
}