#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  daddr; } ;
struct TYPE_8__ {int family; int /*<<< orphan*/  saddr; TYPE_2__ id; int /*<<< orphan*/  reqid; int /*<<< orphan*/  mode; scalar_t__ seq; } ;
struct xfrm_userspi_info {int /*<<< orphan*/  max; int /*<<< orphan*/  min; TYPE_3__ info; } ;
struct TYPE_6__ {int /*<<< orphan*/  daddr; } ;
struct xfrm_state {TYPE_1__ id; } ;
struct xfrm_mark {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  nlsk; } ;
struct net {TYPE_4__ xfrm; } ;
struct TYPE_10__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 TYPE_5__ NETLINK_CB (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 size_t XFRMA_IF_ID ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 struct xfrm_userspi_info* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int verify_spi_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int xfrm_alloc_spi (struct xfrm_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xfrm_state* xfrm_find_acq (struct net*,struct xfrm_mark*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 struct xfrm_state* xfrm_find_acq_byseq (struct net*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xfrm_mark_get (struct nlattr**,struct xfrm_mark*) ; 
 struct sk_buff* xfrm_state_netlink (struct sk_buff*,struct xfrm_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 

__attribute__((used)) static int xfrm_alloc_userspi(struct sk_buff *skb, struct nlmsghdr *nlh,
		struct nlattr **attrs)
{
	struct net *net = sock_net(skb->sk);
	struct xfrm_state *x;
	struct xfrm_userspi_info *p;
	struct sk_buff *resp_skb;
	xfrm_address_t *daddr;
	int family;
	int err;
	u32 mark;
	struct xfrm_mark m;
	u32 if_id = 0;

	p = nlmsg_data(nlh);
	err = verify_spi_info(p->info.id.proto, p->min, p->max);
	if (err)
		goto out_noput;

	family = p->info.family;
	daddr = &p->info.id.daddr;

	x = NULL;

	mark = xfrm_mark_get(attrs, &m);

	if (attrs[XFRMA_IF_ID])
		if_id = nla_get_u32(attrs[XFRMA_IF_ID]);

	if (p->info.seq) {
		x = xfrm_find_acq_byseq(net, mark, p->info.seq);
		if (x && !xfrm_addr_equal(&x->id.daddr, daddr, family)) {
			xfrm_state_put(x);
			x = NULL;
		}
	}

	if (!x)
		x = xfrm_find_acq(net, &m, p->info.mode, p->info.reqid,
				  if_id, p->info.id.proto, daddr,
				  &p->info.saddr, 1,
				  family);
	err = -ENOENT;
	if (x == NULL)
		goto out_noput;

	err = xfrm_alloc_spi(x, p->min, p->max);
	if (err)
		goto out;

	resp_skb = xfrm_state_netlink(skb, x, nlh->nlmsg_seq);
	if (IS_ERR(resp_skb)) {
		err = PTR_ERR(resp_skb);
		goto out;
	}

	err = nlmsg_unicast(net->xfrm.nlsk, resp_skb, NETLINK_CB(skb).portid);

out:
	xfrm_state_put(x);
out_noput:
	return err;
}