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
typedef  int u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {scalar_t__ nlmsg_len; int /*<<< orphan*/  nlmsg_seq; } ;
struct nlmsgerr {int error; int /*<<< orphan*/  msg; } ;
struct nlattr {int dummy; } ;
struct nfgenmsg {int dummy; } ;
struct ip_set {int /*<<< orphan*/  lock; TYPE_1__* variant; } ;
typedef  enum ipset_adt { ____Placeholder_ipset_adt } ipset_adt ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int (* resize ) (struct ip_set*,int) ;int (* uadt ) (struct ip_set*,struct nlattr**,int,int*,int,int) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPSET_ATTR_CMD_MAX ; 
 size_t IPSET_ATTR_LINENO ; 
 int IPSET_ERR_EXIST ; 
 int IPSET_FLAG_EXIST ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 TYPE_2__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_ERROR ; 
 int /*<<< orphan*/  SIZE_MAX ; 
 struct nlmsghdr* __nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_set_adt_policy ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct nlmsghdr*,scalar_t__) ; 
 size_t min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  netlink_unicast (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* nla_data (struct nlattr*) ; 
 int nla_parse (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nlmsgerr* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct nlmsghdr* nlmsg_hdr (struct sk_buff*) ; 
 scalar_t__ nlmsg_len (struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (size_t,int /*<<< orphan*/ ) ; 
 int nlmsg_total_size (int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct ip_set*,int) ; 
 int stub2 (struct ip_set*,struct nlattr**,int,int*,int,int) ; 

__attribute__((used)) static int
call_ad(struct sock *ctnl, struct sk_buff *skb, struct ip_set *set,
	struct nlattr *tb[], enum ipset_adt adt,
	u32 flags, bool use_lineno)
{
	int ret;
	u32 lineno = 0;
	bool eexist = flags & IPSET_FLAG_EXIST, retried = false;

	do {
		spin_lock_bh(&set->lock);
		ret = set->variant->uadt(set, tb, adt, &lineno, flags, retried);
		spin_unlock_bh(&set->lock);
		retried = true;
	} while (ret == -EAGAIN &&
		 set->variant->resize &&
		 (ret = set->variant->resize(set, retried)) == 0);

	if (!ret || (ret == -IPSET_ERR_EXIST && eexist))
		return 0;
	if (lineno && use_lineno) {
		/* Error in restore/batch mode: send back lineno */
		struct nlmsghdr *rep, *nlh = nlmsg_hdr(skb);
		struct sk_buff *skb2;
		struct nlmsgerr *errmsg;
		size_t payload = min(SIZE_MAX,
				     sizeof(*errmsg) + nlmsg_len(nlh));
		int min_len = nlmsg_total_size(sizeof(struct nfgenmsg));
		struct nlattr *cda[IPSET_ATTR_CMD_MAX + 1];
		struct nlattr *cmdattr;
		u32 *errline;

		skb2 = nlmsg_new(payload, GFP_KERNEL);
		if (!skb2)
			return -ENOMEM;
		rep = __nlmsg_put(skb2, NETLINK_CB(skb).portid,
				  nlh->nlmsg_seq, NLMSG_ERROR, payload, 0);
		errmsg = nlmsg_data(rep);
		errmsg->error = ret;
		memcpy(&errmsg->msg, nlh, nlh->nlmsg_len);
		cmdattr = (void *)&errmsg->msg + min_len;

		ret = nla_parse(cda, IPSET_ATTR_CMD_MAX, cmdattr,
				nlh->nlmsg_len - min_len, ip_set_adt_policy,
				NULL);

		if (ret) {
			nlmsg_free(skb2);
			return ret;
		}
		errline = nla_data(cda[IPSET_ATTR_LINENO]);

		*errline = lineno;

		netlink_unicast(ctnl, skb2, NETLINK_CB(skb).portid,
				MSG_DONTWAIT);
		/* Signal netlink not to send its ACK/errmsg.  */
		return -EINTR;
	}

	return ret;
}