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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct pneigh_entry {int flags; scalar_t__ protocol; int /*<<< orphan*/  key; TYPE_1__* dev; } ;
struct nlmsghdr {int dummy; } ;
struct neigh_table {int /*<<< orphan*/  key_len; int /*<<< orphan*/  family; } ;
struct ndmsg {int ndm_flags; int /*<<< orphan*/  ndm_state; int /*<<< orphan*/  ndm_ifindex; int /*<<< orphan*/  ndm_type; scalar_t__ ndm_pad2; scalar_t__ ndm_pad1; int /*<<< orphan*/  ndm_family; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  NDA_DST ; 
 int /*<<< orphan*/  NDA_PROTOCOL ; 
 int NTF_PROXY ; 
 int /*<<< orphan*/  NUD_NONE ; 
 int /*<<< orphan*/  RTN_UNICAST ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct ndmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int) ; 

__attribute__((used)) static int pneigh_fill_info(struct sk_buff *skb, struct pneigh_entry *pn,
			    u32 pid, u32 seq, int type, unsigned int flags,
			    struct neigh_table *tbl)
{
	struct nlmsghdr *nlh;
	struct ndmsg *ndm;

	nlh = nlmsg_put(skb, pid, seq, type, sizeof(*ndm), flags);
	if (nlh == NULL)
		return -EMSGSIZE;

	ndm = nlmsg_data(nlh);
	ndm->ndm_family	 = tbl->family;
	ndm->ndm_pad1    = 0;
	ndm->ndm_pad2    = 0;
	ndm->ndm_flags	 = pn->flags | NTF_PROXY;
	ndm->ndm_type	 = RTN_UNICAST;
	ndm->ndm_ifindex = pn->dev ? pn->dev->ifindex : 0;
	ndm->ndm_state	 = NUD_NONE;

	if (nla_put(skb, NDA_DST, tbl->key_len, pn->key))
		goto nla_put_failure;

	if (pn->protocol && nla_put_u8(skb, NDA_PROTOCOL, pn->protocol))
		goto nla_put_failure;

	nlmsg_end(skb, nlh);
	return 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}