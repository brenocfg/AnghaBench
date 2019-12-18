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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct nlmsghdr {int dummy; } ;
struct ndmsg {int /*<<< orphan*/  ndm_state; int /*<<< orphan*/  ndm_ifindex; scalar_t__ ndm_type; int /*<<< orphan*/  ndm_flags; scalar_t__ ndm_pad2; scalar_t__ ndm_pad1; int /*<<< orphan*/  ndm_family; } ;
struct dsa_slave_dump_ctx {scalar_t__ idx; int /*<<< orphan*/  skb; TYPE_3__* dev; TYPE_2__* cb; } ;
struct TYPE_8__ {int /*<<< orphan*/  portid; } ;
struct TYPE_7__ {int /*<<< orphan*/  ifindex; } ;
struct TYPE_6__ {scalar_t__* args; TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct TYPE_5__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BRIDGE ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NDA_LLADDR ; 
 int /*<<< orphan*/  NDA_VLAN ; 
 TYPE_4__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  NTF_SELF ; 
 int /*<<< orphan*/  NUD_NOARP ; 
 int /*<<< orphan*/  NUD_REACHABLE ; 
 int /*<<< orphan*/  RTM_NEWNEIGH ; 
 scalar_t__ nla_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*) ; 
 scalar_t__ nla_put_u16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nlmsg_cancel (int /*<<< orphan*/ ,struct nlmsghdr*) ; 
 struct ndmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (int /*<<< orphan*/ ,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsa_slave_port_fdb_do_dump(const unsigned char *addr, u16 vid,
			   bool is_static, void *data)
{
	struct dsa_slave_dump_ctx *dump = data;
	u32 portid = NETLINK_CB(dump->cb->skb).portid;
	u32 seq = dump->cb->nlh->nlmsg_seq;
	struct nlmsghdr *nlh;
	struct ndmsg *ndm;

	if (dump->idx < dump->cb->args[2])
		goto skip;

	nlh = nlmsg_put(dump->skb, portid, seq, RTM_NEWNEIGH,
			sizeof(*ndm), NLM_F_MULTI);
	if (!nlh)
		return -EMSGSIZE;

	ndm = nlmsg_data(nlh);
	ndm->ndm_family  = AF_BRIDGE;
	ndm->ndm_pad1    = 0;
	ndm->ndm_pad2    = 0;
	ndm->ndm_flags   = NTF_SELF;
	ndm->ndm_type    = 0;
	ndm->ndm_ifindex = dump->dev->ifindex;
	ndm->ndm_state   = is_static ? NUD_NOARP : NUD_REACHABLE;

	if (nla_put(dump->skb, NDA_LLADDR, ETH_ALEN, addr))
		goto nla_put_failure;

	if (vid && nla_put_u16(dump->skb, NDA_VLAN, vid))
		goto nla_put_failure;

	nlmsg_end(dump->skb, nlh);

skip:
	dump->idx++;
	return 0;

nla_put_failure:
	nlmsg_cancel(dump->skb, nlh);
	return -EMSGSIZE;
}