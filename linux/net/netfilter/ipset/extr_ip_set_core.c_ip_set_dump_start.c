#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int nlmsg_flags; int /*<<< orphan*/  nlmsg_len; } ;
struct netlink_callback {int* args; TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct ip_set_net {int ip_set_max; int is_destroyed; } ;
struct ip_set {int family; int revision; int /*<<< orphan*/  name; TYPE_3__* variant; TYPE_2__* type; int /*<<< orphan*/  ref_netlink; } ;
typedef  int ip_set_id_t ;
struct TYPE_8__ {scalar_t__ portid; } ;
struct TYPE_7__ {int (* head ) (struct ip_set*,struct sk_buff*) ;int (* list ) (struct ip_set*,struct sk_buff*,struct netlink_callback*) ;int /*<<< orphan*/  (* uref ) (struct ip_set*,struct netlink_callback*,int) ;} ;
struct TYPE_6__ {int features; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int DUMP_ALL ; 
 int DUMP_FLAGS (int) ; 
 int DUMP_LAST ; 
 int DUMP_ONE ; 
 int DUMP_TYPE (int) ; 
 int EFAULT ; 
 int EMSGSIZE ; 
 int ENOENT ; 
 int /*<<< orphan*/  IPSET_ATTR_FAMILY ; 
 int /*<<< orphan*/  IPSET_ATTR_INDEX ; 
 int /*<<< orphan*/  IPSET_ATTR_PROTOCOL ; 
 int /*<<< orphan*/  IPSET_ATTR_REVISION ; 
 int /*<<< orphan*/  IPSET_ATTR_SETNAME ; 
 int /*<<< orphan*/  IPSET_ATTR_TYPENAME ; 
 size_t IPSET_CB_ARG0 ; 
 size_t IPSET_CB_DUMP ; 
 size_t IPSET_CB_INDEX ; 
 size_t IPSET_CB_PROTO ; 
 int /*<<< orphan*/  IPSET_CMD_LIST ; 
 int IPSET_DUMP_LAST ; 
 int IPSET_FLAG_LIST_HEADER ; 
 int IPSET_FLAG_LIST_SETNAME ; 
 void* IPSET_INVALID_ID ; 
 int IPSET_PROTOCOL_MIN ; 
 TYPE_4__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int NLM_F_ACK ; 
 unsigned int NLM_F_MULTI ; 
 int /*<<< orphan*/  __ip_set_put_netlink (struct ip_set*) ; 
 int /*<<< orphan*/  dump_attrs (struct nlmsghdr*) ; 
 int dump_init (struct netlink_callback*,struct ip_set_net*) ; 
 int /*<<< orphan*/  htons (int) ; 
 struct ip_set* ip_set (struct ip_set_net*,int) ; 
 struct ip_set_net* ip_set_pernet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_set_ref_lock ; 
 struct ip_set* ip_set_ref_netlink (struct ip_set_net*,int) ; 
 int /*<<< orphan*/  netlink_ack (int /*<<< orphan*/ ,struct nlmsghdr*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nla_put_net16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_hdr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 
 struct nlmsghdr* start_msg (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int stub1 (struct ip_set*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub2 (struct ip_set*,struct netlink_callback*,int) ; 
 int stub3 (struct ip_set*,struct sk_buff*,struct netlink_callback*) ; 
 int /*<<< orphan*/  stub4 (struct ip_set*,struct netlink_callback*,int) ; 
 int /*<<< orphan*/  stub5 (struct ip_set*,struct netlink_callback*,int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ip_set_dump_start(struct sk_buff *skb, struct netlink_callback *cb)
{
	ip_set_id_t index = IPSET_INVALID_ID, max;
	struct ip_set *set = NULL;
	struct nlmsghdr *nlh = NULL;
	unsigned int flags = NETLINK_CB(cb->skb).portid ? NLM_F_MULTI : 0;
	struct ip_set_net *inst = ip_set_pernet(sock_net(skb->sk));
	u32 dump_type, dump_flags;
	bool is_destroyed;
	int ret = 0;

	if (!cb->args[IPSET_CB_DUMP]) {
		ret = dump_init(cb, inst);
		if (ret < 0) {
			nlh = nlmsg_hdr(cb->skb);
			/* We have to create and send the error message
			 * manually :-(
			 */
			if (nlh->nlmsg_flags & NLM_F_ACK)
				netlink_ack(cb->skb, nlh, ret, NULL);
			return ret;
		}
	}

	if (cb->args[IPSET_CB_INDEX] >= inst->ip_set_max)
		goto out;

	dump_type = DUMP_TYPE(cb->args[IPSET_CB_DUMP]);
	dump_flags = DUMP_FLAGS(cb->args[IPSET_CB_DUMP]);
	max = dump_type == DUMP_ONE ? cb->args[IPSET_CB_INDEX] + 1
				    : inst->ip_set_max;
dump_last:
	pr_debug("dump type, flag: %u %u index: %ld\n",
		 dump_type, dump_flags, cb->args[IPSET_CB_INDEX]);
	for (; cb->args[IPSET_CB_INDEX] < max; cb->args[IPSET_CB_INDEX]++) {
		index = (ip_set_id_t)cb->args[IPSET_CB_INDEX];
		write_lock_bh(&ip_set_ref_lock);
		set = ip_set(inst, index);
		is_destroyed = inst->is_destroyed;
		if (!set || is_destroyed) {
			write_unlock_bh(&ip_set_ref_lock);
			if (dump_type == DUMP_ONE) {
				ret = -ENOENT;
				goto out;
			}
			if (is_destroyed) {
				/* All sets are just being destroyed */
				ret = 0;
				goto out;
			}
			continue;
		}
		/* When dumping all sets, we must dump "sorted"
		 * so that lists (unions of sets) are dumped last.
		 */
		if (dump_type != DUMP_ONE &&
		    ((dump_type == DUMP_ALL) ==
		     !!(set->type->features & IPSET_DUMP_LAST))) {
			write_unlock_bh(&ip_set_ref_lock);
			continue;
		}
		pr_debug("List set: %s\n", set->name);
		if (!cb->args[IPSET_CB_ARG0]) {
			/* Start listing: make sure set won't be destroyed */
			pr_debug("reference set\n");
			set->ref_netlink++;
		}
		write_unlock_bh(&ip_set_ref_lock);
		nlh = start_msg(skb, NETLINK_CB(cb->skb).portid,
				cb->nlh->nlmsg_seq, flags,
				IPSET_CMD_LIST);
		if (!nlh) {
			ret = -EMSGSIZE;
			goto release_refcount;
		}
		if (nla_put_u8(skb, IPSET_ATTR_PROTOCOL,
			       cb->args[IPSET_CB_PROTO]) ||
		    nla_put_string(skb, IPSET_ATTR_SETNAME, set->name))
			goto nla_put_failure;
		if (dump_flags & IPSET_FLAG_LIST_SETNAME)
			goto next_set;
		switch (cb->args[IPSET_CB_ARG0]) {
		case 0:
			/* Core header data */
			if (nla_put_string(skb, IPSET_ATTR_TYPENAME,
					   set->type->name) ||
			    nla_put_u8(skb, IPSET_ATTR_FAMILY,
				       set->family) ||
			    nla_put_u8(skb, IPSET_ATTR_REVISION,
				       set->revision))
				goto nla_put_failure;
			if (cb->args[IPSET_CB_PROTO] > IPSET_PROTOCOL_MIN &&
			    nla_put_net16(skb, IPSET_ATTR_INDEX, htons(index)))
				goto nla_put_failure;
			ret = set->variant->head(set, skb);
			if (ret < 0)
				goto release_refcount;
			if (dump_flags & IPSET_FLAG_LIST_HEADER)
				goto next_set;
			if (set->variant->uref)
				set->variant->uref(set, cb, true);
			/* fall through */
		default:
			ret = set->variant->list(set, skb, cb);
			if (!cb->args[IPSET_CB_ARG0])
				/* Set is done, proceed with next one */
				goto next_set;
			goto release_refcount;
		}
	}
	/* If we dump all sets, continue with dumping last ones */
	if (dump_type == DUMP_ALL) {
		dump_type = DUMP_LAST;
		cb->args[IPSET_CB_DUMP] = dump_type | (dump_flags << 16);
		cb->args[IPSET_CB_INDEX] = 0;
		if (set && set->variant->uref)
			set->variant->uref(set, cb, false);
		goto dump_last;
	}
	goto out;

nla_put_failure:
	ret = -EFAULT;
next_set:
	if (dump_type == DUMP_ONE)
		cb->args[IPSET_CB_INDEX] = IPSET_INVALID_ID;
	else
		cb->args[IPSET_CB_INDEX]++;
release_refcount:
	/* If there was an error or set is done, release set */
	if (ret || !cb->args[IPSET_CB_ARG0]) {
		set = ip_set_ref_netlink(inst, index);
		if (set->variant->uref)
			set->variant->uref(set, cb, false);
		pr_debug("release set %s\n", set->name);
		__ip_set_put_netlink(set);
		cb->args[IPSET_CB_ARG0] = 0;
	}
out:
	if (nlh) {
		nlmsg_end(skb, nlh);
		pr_debug("nlmsg_len: %u\n", nlh->nlmsg_len);
		dump_attrs(nlh);
	}

	return ret < 0 ? ret : skb->len;
}