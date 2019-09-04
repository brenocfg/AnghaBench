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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int len; int /*<<< orphan*/  dev; } ;
struct rs_msg {int /*<<< orphan*/  opt; } ;
struct neighbour {int dummy; } ;
struct ndisc_options {scalar_t__ nd_opts_src_lladdr; } ;
struct TYPE_3__ {int /*<<< orphan*/  forwarding; } ;
struct inet6_dev {TYPE_1__ cnf; } ;
struct in6_addr {int dummy; } ;
struct TYPE_4__ {struct in6_addr saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDISC_ROUTER_SOLICITATION ; 
 int /*<<< orphan*/  ND_PRINTK (int,int /*<<< orphan*/ ,char*) ; 
 int NEIGH_UPDATE_F_OVERRIDE ; 
 int NEIGH_UPDATE_F_OVERRIDE_ISROUTER ; 
 int NEIGH_UPDATE_F_WEAK_OVERRIDE ; 
 int /*<<< orphan*/  NUD_STALE ; 
 struct inet6_dev* __in6_dev_get (int /*<<< orphan*/ ) ; 
 struct neighbour* __neigh_lookup (int /*<<< orphan*/ *,struct in6_addr const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  err ; 
 scalar_t__ ipv6_addr_any (struct in6_addr const*) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  nd_tbl ; 
 int /*<<< orphan*/ * ndisc_opt_addr_data (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndisc_parse_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,struct ndisc_options*) ; 
 int /*<<< orphan*/  ndisc_update (int /*<<< orphan*/ ,struct neighbour*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ndisc_options*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  notice ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 

__attribute__((used)) static void ndisc_recv_rs(struct sk_buff *skb)
{
	struct rs_msg *rs_msg = (struct rs_msg *)skb_transport_header(skb);
	unsigned long ndoptlen = skb->len - sizeof(*rs_msg);
	struct neighbour *neigh;
	struct inet6_dev *idev;
	const struct in6_addr *saddr = &ipv6_hdr(skb)->saddr;
	struct ndisc_options ndopts;
	u8 *lladdr = NULL;

	if (skb->len < sizeof(*rs_msg))
		return;

	idev = __in6_dev_get(skb->dev);
	if (!idev) {
		ND_PRINTK(1, err, "RS: can't find in6 device\n");
		return;
	}

	/* Don't accept RS if we're not in router mode */
	if (!idev->cnf.forwarding)
		goto out;

	/*
	 * Don't update NCE if src = ::;
	 * this implies that the source node has no ip address assigned yet.
	 */
	if (ipv6_addr_any(saddr))
		goto out;

	/* Parse ND options */
	if (!ndisc_parse_options(skb->dev, rs_msg->opt, ndoptlen, &ndopts)) {
		ND_PRINTK(2, notice, "NS: invalid ND option, ignored\n");
		goto out;
	}

	if (ndopts.nd_opts_src_lladdr) {
		lladdr = ndisc_opt_addr_data(ndopts.nd_opts_src_lladdr,
					     skb->dev);
		if (!lladdr)
			goto out;
	}

	neigh = __neigh_lookup(&nd_tbl, saddr, skb->dev, 1);
	if (neigh) {
		ndisc_update(skb->dev, neigh, lladdr, NUD_STALE,
			     NEIGH_UPDATE_F_WEAK_OVERRIDE|
			     NEIGH_UPDATE_F_OVERRIDE|
			     NEIGH_UPDATE_F_OVERRIDE_ISROUTER,
			     NDISC_ROUTER_SOLICITATION, &ndopts);
		neigh_release(neigh);
	}
out:
	return;
}