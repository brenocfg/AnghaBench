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
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  mark; } ;
struct seg6_lwt {int /*<<< orphan*/  cache; } ;
struct net {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  nexthdr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct flowi6 {int /*<<< orphan*/  saddr; int /*<<< orphan*/  flowi6_proto; int /*<<< orphan*/  flowi6_mark; int /*<<< orphan*/  flowlabel; int /*<<< orphan*/  daddr; } ;
struct dst_entry {int error; int /*<<< orphan*/  dev; int /*<<< orphan*/  lwtstate; } ;
typedef  int /*<<< orphan*/  fl6 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LL_RESERVED_SPACE (int /*<<< orphan*/ ) ; 
 struct dst_entry* dst_cache_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_cache_set_ip6 (int /*<<< orphan*/ *,struct dst_entry*,int /*<<< orphan*/ *) ; 
 int dst_output (struct net*,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  ip6_flowinfo (struct ipv6hdr*) ; 
 struct dst_entry* ip6_route_output (struct net*,int /*<<< orphan*/ *,struct flowi6*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct flowi6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int seg6_do_srh (struct sk_buff*) ; 
 struct seg6_lwt* seg6_lwt_lwtunnel (int /*<<< orphan*/ ) ; 
 int skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int seg6_output(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	struct dst_entry *orig_dst = skb_dst(skb);
	struct dst_entry *dst = NULL;
	struct seg6_lwt *slwt;
	int err = -EINVAL;

	err = seg6_do_srh(skb);
	if (unlikely(err))
		goto drop;

	slwt = seg6_lwt_lwtunnel(orig_dst->lwtstate);

	preempt_disable();
	dst = dst_cache_get(&slwt->cache);
	preempt_enable();

	if (unlikely(!dst)) {
		struct ipv6hdr *hdr = ipv6_hdr(skb);
		struct flowi6 fl6;

		memset(&fl6, 0, sizeof(fl6));
		fl6.daddr = hdr->daddr;
		fl6.saddr = hdr->saddr;
		fl6.flowlabel = ip6_flowinfo(hdr);
		fl6.flowi6_mark = skb->mark;
		fl6.flowi6_proto = hdr->nexthdr;

		dst = ip6_route_output(net, NULL, &fl6);
		if (dst->error) {
			err = dst->error;
			dst_release(dst);
			goto drop;
		}

		preempt_disable();
		dst_cache_set_ip6(&slwt->cache, dst, &fl6.saddr);
		preempt_enable();
	}

	skb_dst_drop(skb);
	skb_dst_set(skb, dst);

	err = skb_cow_head(skb, LL_RESERVED_SPACE(dst->dev));
	if (unlikely(err))
		goto drop;

	return dst_output(net, sk, skb);
drop:
	kfree_skb(skb);
	return err;
}