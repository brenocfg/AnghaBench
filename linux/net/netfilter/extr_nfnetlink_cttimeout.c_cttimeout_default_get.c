#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_type; int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct nf_conntrack_l4proto {int l4proto; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
typedef  int __u8 ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_18__ {int /*<<< orphan*/  portid; } ;
struct TYPE_17__ {unsigned int* dccp_timeout; } ;
struct TYPE_16__ {unsigned int timeout; } ;
struct TYPE_15__ {unsigned int* timeouts; } ;
struct TYPE_14__ {unsigned int timeout; } ;
struct TYPE_13__ {unsigned int timeout; } ;
struct TYPE_12__ {unsigned int* timeouts; } ;
struct TYPE_11__ {unsigned int* timeouts; } ;
struct TYPE_10__ {unsigned int* timeouts; } ;

/* Variables and functions */
 size_t CTA_TIMEOUT_L3PROTO ; 
 size_t CTA_TIMEOUT_L4PROTO ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPCTNL_MSG_TIMEOUT_DEFAULT_SET ; 
#define  IPPROTO_DCCP 135 
#define  IPPROTO_GRE 134 
#define  IPPROTO_ICMP 133 
#define  IPPROTO_ICMPV6 132 
#define  IPPROTO_SCTP 131 
#define  IPPROTO_TCP 130 
#define  IPPROTO_UDP 129 
#define  IPPROTO_UDPLITE 128 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 TYPE_9__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NFNL_MSG_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int cttimeout_default_fill_info (struct net*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nf_conntrack_l4proto const*,unsigned int*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int netlink_unicast (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nf_conntrack_l4proto* nf_ct_l4proto_find (int) ; 
 TYPE_8__* nf_dccp_pernet (struct net*) ; 
 TYPE_7__* nf_generic_pernet (struct net*) ; 
 TYPE_6__* nf_gre_pernet (struct net*) ; 
 TYPE_5__* nf_icmp_pernet (struct net*) ; 
 TYPE_4__* nf_icmpv6_pernet (struct net*) ; 
 TYPE_3__* nf_sctp_pernet (struct net*) ; 
 TYPE_2__* nf_tcp_pernet (struct net*) ; 
 TYPE_1__* nf_udp_pernet (struct net*) ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr const* const) ; 
 int nla_get_u8 (struct nlattr const* const) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cttimeout_default_get(struct net *net, struct sock *ctnl,
				 struct sk_buff *skb,
				 const struct nlmsghdr *nlh,
				 const struct nlattr * const cda[],
				 struct netlink_ext_ack *extack)
{
	const struct nf_conntrack_l4proto *l4proto;
	unsigned int *timeouts = NULL;
	struct sk_buff *skb2;
	int ret, err;
	__u16 l3num;
	__u8 l4num;

	if (!cda[CTA_TIMEOUT_L3PROTO] || !cda[CTA_TIMEOUT_L4PROTO])
		return -EINVAL;

	l3num = ntohs(nla_get_be16(cda[CTA_TIMEOUT_L3PROTO]));
	l4num = nla_get_u8(cda[CTA_TIMEOUT_L4PROTO]);
	l4proto = nf_ct_l4proto_find(l4num);

	err = -EOPNOTSUPP;
	if (l4proto->l4proto != l4num)
		goto err;

	switch (l4proto->l4proto) {
	case IPPROTO_ICMP:
		timeouts = &nf_icmp_pernet(net)->timeout;
		break;
	case IPPROTO_TCP:
		timeouts = nf_tcp_pernet(net)->timeouts;
		break;
	case IPPROTO_UDP: /* fallthrough */
	case IPPROTO_UDPLITE:
		timeouts = nf_udp_pernet(net)->timeouts;
		break;
	case IPPROTO_DCCP:
#ifdef CONFIG_NF_CT_PROTO_DCCP
		timeouts = nf_dccp_pernet(net)->dccp_timeout;
#endif
		break;
	case IPPROTO_ICMPV6:
		timeouts = &nf_icmpv6_pernet(net)->timeout;
		break;
	case IPPROTO_SCTP:
#ifdef CONFIG_NF_CT_PROTO_SCTP
		timeouts = nf_sctp_pernet(net)->timeouts;
#endif
		break;
	case IPPROTO_GRE:
#ifdef CONFIG_NF_CT_PROTO_GRE
		timeouts = nf_gre_pernet(net)->timeouts;
#endif
		break;
	case 255:
		timeouts = &nf_generic_pernet(net)->timeout;
		break;
	default:
		WARN_ONCE(1, "Missing timeouts for proto %d", l4proto->l4proto);
		break;
	}

	if (!timeouts)
		goto err;

	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (skb2 == NULL) {
		err = -ENOMEM;
		goto err;
	}

	ret = cttimeout_default_fill_info(net, skb2, NETLINK_CB(skb).portid,
					  nlh->nlmsg_seq,
					  NFNL_MSG_TYPE(nlh->nlmsg_type),
					  IPCTNL_MSG_TIMEOUT_DEFAULT_SET,
					  l3num, l4proto, timeouts);
	if (ret <= 0) {
		kfree_skb(skb2);
		err = -ENOMEM;
		goto err;
	}
	ret = netlink_unicast(ctnl, skb2, NETLINK_CB(skb).portid, MSG_DONTWAIT);
	if (ret > 0)
		ret = 0;

	/* this avoids a loop in nfnetlink. */
	return ret == -EAGAIN ? -ENOBUFS : ret;
err:
	return err;
}