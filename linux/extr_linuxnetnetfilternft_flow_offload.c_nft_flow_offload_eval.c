#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  code; } ;
struct nft_regs {TYPE_6__ verdict; } ;
struct nft_pktinfo {int /*<<< orphan*/  skb; } ;
struct nft_flow_offload {TYPE_1__* flowtable; } ;
struct nft_expr {int dummy; } ;
struct nf_flowtable {int dummy; } ;
struct nf_flow_route {TYPE_5__* tuple; } ;
struct nf_conn_help {int dummy; } ;
struct nf_conn {int /*<<< orphan*/  status; TYPE_4__* tuplehash; } ;
struct flow_offload {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
struct TYPE_11__ {int /*<<< orphan*/  dst; } ;
struct TYPE_8__ {int protonum; } ;
struct TYPE_9__ {TYPE_2__ dst; } ;
struct TYPE_10__ {TYPE_3__ tuple; } ;
struct TYPE_7__ {struct nf_flowtable data; } ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  IPS_OFFLOAD_BIT ; 
 size_t IP_CT_DIR_ORIGINAL ; 
 int IP_CT_NEW ; 
 int IP_CT_RELATED ; 
 int /*<<< orphan*/  NFT_BREAK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ ) ; 
 int flow_offload_add (struct nf_flowtable*,struct flow_offload*) ; 
 struct flow_offload* flow_offload_alloc (struct nf_conn*,struct nf_flow_route*) ; 
 int /*<<< orphan*/  flow_offload_free (struct flow_offload*) ; 
 struct nf_conn* nf_ct_get (int /*<<< orphan*/ ,int*) ; 
 struct nf_conn_help* nfct_help (struct nf_conn*) ; 
 struct nft_flow_offload* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nft_flow_offload_skip (int /*<<< orphan*/ ) ; 
 scalar_t__ nft_flow_route (struct nft_pktinfo const*,struct nf_conn*,struct nf_flow_route*,int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nft_flow_offload_eval(const struct nft_expr *expr,
				  struct nft_regs *regs,
				  const struct nft_pktinfo *pkt)
{
	struct nft_flow_offload *priv = nft_expr_priv(expr);
	struct nf_flowtable *flowtable = &priv->flowtable->data;
	const struct nf_conn_help *help;
	enum ip_conntrack_info ctinfo;
	struct nf_flow_route route;
	struct flow_offload *flow;
	enum ip_conntrack_dir dir;
	struct nf_conn *ct;
	int ret;

	if (nft_flow_offload_skip(pkt->skb))
		goto out;

	ct = nf_ct_get(pkt->skb, &ctinfo);
	if (!ct)
		goto out;

	switch (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum) {
	case IPPROTO_TCP:
	case IPPROTO_UDP:
		break;
	default:
		goto out;
	}

	help = nfct_help(ct);
	if (help)
		goto out;

	if (ctinfo == IP_CT_NEW ||
	    ctinfo == IP_CT_RELATED)
		goto out;

	if (test_and_set_bit(IPS_OFFLOAD_BIT, &ct->status))
		goto out;

	dir = CTINFO2DIR(ctinfo);
	if (nft_flow_route(pkt, ct, &route, dir) < 0)
		goto err_flow_route;

	flow = flow_offload_alloc(ct, &route);
	if (!flow)
		goto err_flow_alloc;

	ret = flow_offload_add(flowtable, flow);
	if (ret < 0)
		goto err_flow_add;

	return;

err_flow_add:
	flow_offload_free(flow);
err_flow_alloc:
	dst_release(route.tuple[!dir].dst);
err_flow_route:
	clear_bit(IPS_OFFLOAD_BIT, &ct->status);
out:
	regs->verdict.code = NFT_BREAK;
}