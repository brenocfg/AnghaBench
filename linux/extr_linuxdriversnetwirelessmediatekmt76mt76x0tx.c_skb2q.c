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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int MT_TXQ_BE ; 
 int MT_TXQ_PSD ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  q2hwq (int) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sk_buff*,int) ; 

__attribute__((used)) static u8 skb2q(struct sk_buff *skb)
{
	int qid = skb_get_queue_mapping(skb);

	if (WARN_ON(qid >= MT_TXQ_PSD)) {
		qid = MT_TXQ_BE;
		skb_set_queue_mapping(skb, qid);
	}

	return q2hwq(qid);
}