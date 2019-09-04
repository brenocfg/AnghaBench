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
typedef  int /*<<< orphan*/  u32 ;
struct xt_action_param {struct xt_NFQ_info_v1* targinfo; } ;
struct xt_NFQ_info_v1 {int queues_total; int /*<<< orphan*/  queuenum; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 unsigned int NF_QUEUE_NR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jhash_initval ; 
 int /*<<< orphan*/  nfqueue_hash (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xt_family (struct xt_action_param const*) ; 

__attribute__((used)) static unsigned int
nfqueue_tg_v1(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_NFQ_info_v1 *info = par->targinfo;
	u32 queue = info->queuenum;

	if (info->queues_total > 1) {
		queue = nfqueue_hash(skb, queue, info->queues_total,
				     xt_family(par), jhash_initval);
	}
	return NF_QUEUE_NR(queue);
}