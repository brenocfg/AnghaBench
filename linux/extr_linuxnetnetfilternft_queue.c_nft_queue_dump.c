#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nft_queue {int /*<<< orphan*/  flags; int /*<<< orphan*/  queues_total; int /*<<< orphan*/  queuenum; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_QUEUE_FLAGS ; 
 int /*<<< orphan*/  NFTA_QUEUE_NUM ; 
 int /*<<< orphan*/  NFTA_QUEUE_TOTAL ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct nft_queue* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_queue_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	const struct nft_queue *priv = nft_expr_priv(expr);

	if (nla_put_be16(skb, NFTA_QUEUE_NUM, htons(priv->queuenum)) ||
	    nla_put_be16(skb, NFTA_QUEUE_TOTAL, htons(priv->queues_total)) ||
	    nla_put_be16(skb, NFTA_QUEUE_FLAGS, htons(priv->flags)))
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -1;
}