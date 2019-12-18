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
struct napi_struct {struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRO_MAX_HEAD ; 
 struct sk_buff* napi_alloc_skb (struct napi_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_mark_napi_id (struct sk_buff*,struct napi_struct*) ; 

struct sk_buff *napi_get_frags(struct napi_struct *napi)
{
	struct sk_buff *skb = napi->skb;

	if (!skb) {
		skb = napi_alloc_skb(napi, GRO_MAX_HEAD);
		if (skb) {
			napi->skb = skb;
			skb_mark_napi_id(skb, napi);
		}
	}
	return skb;
}