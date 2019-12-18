#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nft_regs {int dummy; } ;
struct nft_pktinfo {int /*<<< orphan*/  skb; } ;
struct TYPE_4__ {scalar_t__ level; } ;
struct TYPE_5__ {TYPE_1__ log; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_2__ u; } ;
struct nft_log {int /*<<< orphan*/  prefix; TYPE_3__ loginfo; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 scalar_t__ NFT_LOGLEVEL_AUDIT ; 
 scalar_t__ NF_LOG_TYPE_LOG ; 
 int /*<<< orphan*/  nf_log_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 struct nft_log* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_hook (struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  nft_in (struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  nft_log_eval_audit (struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  nft_net (struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  nft_out (struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  nft_pf (struct nft_pktinfo const*) ; 

__attribute__((used)) static void nft_log_eval(const struct nft_expr *expr,
			 struct nft_regs *regs,
			 const struct nft_pktinfo *pkt)
{
	const struct nft_log *priv = nft_expr_priv(expr);

	if (priv->loginfo.type == NF_LOG_TYPE_LOG &&
	    priv->loginfo.u.log.level == NFT_LOGLEVEL_AUDIT) {
		nft_log_eval_audit(pkt);
		return;
	}

	nf_log_packet(nft_net(pkt), nft_pf(pkt), nft_hook(pkt), pkt->skb,
		      nft_in(pkt), nft_out(pkt), &priv->loginfo, "%s",
		      priv->prefix);
}