#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct tcphdr {int /*<<< orphan*/  rst; int /*<<< orphan*/  fin; } ;
struct TYPE_11__ {int /*<<< orphan*/  code; } ;
struct nft_regs {TYPE_10__ verdict; } ;
struct TYPE_16__ {int /*<<< orphan*/  thoff; } ;
struct nft_pktinfo {TYPE_5__ xt; int /*<<< orphan*/  skb; } ;
struct nft_flow_offload {TYPE_1__* flowtable; } ;
struct nft_expr {int dummy; } ;
struct nf_flowtable {int dummy; } ;
struct nf_flow_route {TYPE_9__* tuple; } ;
struct TYPE_18__ {TYPE_6__* seen; } ;
struct TYPE_19__ {TYPE_7__ tcp; } ;
struct nf_conn {int status; TYPE_8__ proto; TYPE_4__* tuplehash; } ;
struct flow_offload {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
typedef  int /*<<< orphan*/  _tcph ;
struct TYPE_20__ {int /*<<< orphan*/  dst; } ;
struct TYPE_17__ {int /*<<< orphan*/  flags; } ;
struct TYPE_13__ {int protonum; } ;
struct TYPE_14__ {TYPE_2__ dst; } ;
struct TYPE_15__ {TYPE_3__ tuple; } ;
struct TYPE_12__ {struct nf_flowtable data; } ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  IPS_OFFLOAD_BIT ; 
 int IPS_SEQ_ADJUST ; 
 size_t IP_CT_DIR_ORIGINAL ; 
 int /*<<< orphan*/  IP_CT_TCP_FLAG_BE_LIBERAL ; 
 int /*<<< orphan*/  NFT_BREAK ; 
 int /*<<< orphan*/  NF_CT_EXT_HELPER ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ ) ; 
 int flow_offload_add (struct nf_flowtable*,struct flow_offload*) ; 
 struct flow_offload* flow_offload_alloc (struct nf_conn*,struct nf_flow_route*) ; 
 int /*<<< orphan*/  flow_offload_free (struct flow_offload*) ; 
 scalar_t__ nf_ct_ext_exist (struct nf_conn*,int /*<<< orphan*/ ) ; 
 struct nf_conn* nf_ct_get (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  nf_ct_is_confirmed (struct nf_conn*) ; 
 struct nft_flow_offload* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nft_flow_offload_skip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nft_flow_route (struct nft_pktinfo const*,struct nf_conn*,struct nf_flow_route*,int) ; 
 int /*<<< orphan*/  nft_pf (struct nft_pktinfo const*) ; 
 struct tcphdr* skb_header_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct tcphdr*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static void nft_flow_offload_eval(const struct nft_expr *expr,
				  struct nft_regs *regs,
				  const struct nft_pktinfo *pkt)
{
	struct nft_flow_offload *priv = nft_expr_priv(expr);
	struct nf_flowtable *flowtable = &priv->flowtable->data;
	struct tcphdr _tcph, *tcph = NULL;
	enum ip_conntrack_info ctinfo;
	struct nf_flow_route route;
	struct flow_offload *flow;
	enum ip_conntrack_dir dir;
	struct nf_conn *ct;
	int ret;

	if (nft_flow_offload_skip(pkt->skb, nft_pf(pkt)))
		goto out;

	ct = nf_ct_get(pkt->skb, &ctinfo);
	if (!ct)
		goto out;

	switch (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum) {
	case IPPROTO_TCP:
		tcph = skb_header_pointer(pkt->skb, pkt->xt.thoff,
					  sizeof(_tcph), &_tcph);
		if (unlikely(!tcph || tcph->fin || tcph->rst))
			goto out;
		break;
	case IPPROTO_UDP:
		break;
	default:
		goto out;
	}

	if (nf_ct_ext_exist(ct, NF_CT_EXT_HELPER) ||
	    ct->status & IPS_SEQ_ADJUST)
		goto out;

	if (!nf_ct_is_confirmed(ct))
		goto out;

	if (test_and_set_bit(IPS_OFFLOAD_BIT, &ct->status))
		goto out;

	dir = CTINFO2DIR(ctinfo);
	if (nft_flow_route(pkt, ct, &route, dir) < 0)
		goto err_flow_route;

	flow = flow_offload_alloc(ct, &route);
	if (!flow)
		goto err_flow_alloc;

	if (tcph) {
		ct->proto.tcp.seen[0].flags |= IP_CT_TCP_FLAG_BE_LIBERAL;
		ct->proto.tcp.seen[1].flags |= IP_CT_TCP_FLAG_BE_LIBERAL;
	}

	ret = flow_offload_add(flowtable, flow);
	if (ret < 0)
		goto err_flow_add;

	dst_release(route.tuple[!dir].dst);
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