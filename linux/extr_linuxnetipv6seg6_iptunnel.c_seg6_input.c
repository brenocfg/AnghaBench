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
struct seg6_lwt {int /*<<< orphan*/  cache; } ;
struct dst_entry {int /*<<< orphan*/  dev; int /*<<< orphan*/  error; int /*<<< orphan*/  lwtstate; } ;
struct TYPE_2__ {int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_RESERVED_SPACE (int /*<<< orphan*/ ) ; 
 struct dst_entry* dst_cache_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_cache_set_ip6 (int /*<<< orphan*/ *,struct dst_entry*,int /*<<< orphan*/ *) ; 
 int dst_input (struct sk_buff*) ; 
 int /*<<< orphan*/  ip6_route_input (struct sk_buff*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int seg6_do_srh (struct sk_buff*) ; 
 struct seg6_lwt* seg6_lwt_lwtunnel (int /*<<< orphan*/ ) ; 
 int skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int seg6_input(struct sk_buff *skb)
{
	struct dst_entry *orig_dst = skb_dst(skb);
	struct dst_entry *dst = NULL;
	struct seg6_lwt *slwt;
	int err;

	err = seg6_do_srh(skb);
	if (unlikely(err)) {
		kfree_skb(skb);
		return err;
	}

	slwt = seg6_lwt_lwtunnel(orig_dst->lwtstate);

	preempt_disable();
	dst = dst_cache_get(&slwt->cache);
	preempt_enable();

	skb_dst_drop(skb);

	if (!dst) {
		ip6_route_input(skb);
		dst = skb_dst(skb);
		if (!dst->error) {
			preempt_disable();
			dst_cache_set_ip6(&slwt->cache, dst,
					  &ipv6_hdr(skb)->saddr);
			preempt_enable();
		}
	} else {
		skb_dst_set(skb, dst);
	}

	err = skb_cow_head(skb, LL_RESERVED_SPACE(dst->dev));
	if (unlikely(err))
		return err;

	return dst_input(skb);
}