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
struct sk_buff {int dummy; } ;
typedef  int gro_result_t ;
struct TYPE_2__ {int /*<<< orphan*/  free; } ;

/* Variables and functions */
#define  GRO_CONSUMED 133 
#define  GRO_DROP 132 
#define  GRO_HELD 131 
#define  GRO_MERGED 130 
#define  GRO_MERGED_FREE 129 
#define  GRO_NORMAL 128 
 TYPE_1__* NAPI_GRO_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NAPI_GRO_FREE_STOLEN_HEAD ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  napi_skb_free_stolen_head (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_receive_skb_internal (struct sk_buff*) ; 

__attribute__((used)) static gro_result_t napi_skb_finish(gro_result_t ret, struct sk_buff *skb)
{
	switch (ret) {
	case GRO_NORMAL:
		if (netif_receive_skb_internal(skb))
			ret = GRO_DROP;
		break;

	case GRO_DROP:
		kfree_skb(skb);
		break;

	case GRO_MERGED_FREE:
		if (NAPI_GRO_CB(skb)->free == NAPI_GRO_FREE_STOLEN_HEAD)
			napi_skb_free_stolen_head(skb);
		else
			__kfree_skb(skb);
		break;

	case GRO_HELD:
	case GRO_MERGED:
	case GRO_CONSUMED:
		break;
	}

	return ret;
}