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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ code; } ;
struct nft_regs {TYPE_1__ verdict; } ;
struct nft_queue {int queues_total; int flags; scalar_t__ queuenum; } ;
struct nft_pktinfo {int /*<<< orphan*/  skb; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int NFT_QUEUE_FLAG_BYPASS ; 
 int NFT_QUEUE_FLAG_CPU_FANOUT ; 
 scalar_t__ NF_QUEUE_NR (scalar_t__) ; 
 scalar_t__ NF_VERDICT_FLAG_QUEUE_BYPASS ; 
 int /*<<< orphan*/  jhash_initval ; 
 scalar_t__ nfqueue_hash (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_queue* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_pf (struct nft_pktinfo const*) ; 
 int raw_smp_processor_id () ; 

__attribute__((used)) static void nft_queue_eval(const struct nft_expr *expr,
			   struct nft_regs *regs,
			   const struct nft_pktinfo *pkt)
{
	struct nft_queue *priv = nft_expr_priv(expr);
	u32 queue = priv->queuenum;
	u32 ret;

	if (priv->queues_total > 1) {
		if (priv->flags & NFT_QUEUE_FLAG_CPU_FANOUT) {
			int cpu = raw_smp_processor_id();

			queue = priv->queuenum + cpu % priv->queues_total;
		} else {
			queue = nfqueue_hash(pkt->skb, queue,
					     priv->queues_total, nft_pf(pkt),
					     jhash_initval);
		}
	}

	ret = NF_QUEUE_NR(queue);
	if (priv->flags & NFT_QUEUE_FLAG_BYPASS)
		ret |= NF_VERDICT_FLAG_QUEUE_BYPASS;

	regs->verdict.code = ret;
}