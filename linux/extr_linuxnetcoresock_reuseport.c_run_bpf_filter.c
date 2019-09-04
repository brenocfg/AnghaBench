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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct sock_reuseport {struct sock** socks; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int) ; 
 size_t bpf_prog_run_save_cb (struct bpf_prog*,struct sk_buff*) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_pull (struct sk_buff*,int) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_shared (struct sk_buff*) ; 

__attribute__((used)) static struct sock *run_bpf_filter(struct sock_reuseport *reuse, u16 socks,
				   struct bpf_prog *prog, struct sk_buff *skb,
				   int hdr_len)
{
	struct sk_buff *nskb = NULL;
	u32 index;

	if (skb_shared(skb)) {
		nskb = skb_clone(skb, GFP_ATOMIC);
		if (!nskb)
			return NULL;
		skb = nskb;
	}

	/* temporarily advance data past protocol header */
	if (!pskb_pull(skb, hdr_len)) {
		kfree_skb(nskb);
		return NULL;
	}
	index = bpf_prog_run_save_cb(prog, skb);
	__skb_push(skb, hdr_len);

	consume_skb(nskb);

	if (index >= socks)
		return NULL;

	return reuse->socks[index];
}