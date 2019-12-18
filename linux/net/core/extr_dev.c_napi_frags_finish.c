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
struct sk_buff {int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; } ;
struct napi_struct {int dummy; } ;
typedef  int gro_result_t ;
struct TYPE_2__ {int /*<<< orphan*/  free; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
#define  GRO_CONSUMED 133 
#define  GRO_DROP 132 
#define  GRO_HELD 131 
#define  GRO_MERGED 130 
#define  GRO_MERGED_FREE 129 
#define  GRO_NORMAL 128 
 TYPE_1__* NAPI_GRO_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NAPI_GRO_FREE_STOLEN_HEAD ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gro_normal_one (struct napi_struct*,struct sk_buff*) ; 
 int /*<<< orphan*/  napi_reuse_skb (struct napi_struct*,struct sk_buff*) ; 
 int /*<<< orphan*/  napi_skb_free_stolen_head (struct sk_buff*) ; 

__attribute__((used)) static gro_result_t napi_frags_finish(struct napi_struct *napi,
				      struct sk_buff *skb,
				      gro_result_t ret)
{
	switch (ret) {
	case GRO_NORMAL:
	case GRO_HELD:
		__skb_push(skb, ETH_HLEN);
		skb->protocol = eth_type_trans(skb, skb->dev);
		if (ret == GRO_NORMAL)
			gro_normal_one(napi, skb);
		break;

	case GRO_DROP:
		napi_reuse_skb(napi, skb);
		break;

	case GRO_MERGED_FREE:
		if (NAPI_GRO_CB(skb)->free == NAPI_GRO_FREE_STOLEN_HEAD)
			napi_skb_free_stolen_head(skb);
		else
			napi_reuse_skb(napi, skb);
		break;

	case GRO_MERGED:
	case GRO_CONSUMED:
		break;
	}

	return ret;
}