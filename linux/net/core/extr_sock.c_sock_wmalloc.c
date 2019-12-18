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
struct sock {int /*<<< orphan*/  sk_sndbuf; int /*<<< orphan*/  sk_wmem_alloc; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 struct sk_buff* alloc_skb (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,struct sock*) ; 

struct sk_buff *sock_wmalloc(struct sock *sk, unsigned long size, int force,
			     gfp_t priority)
{
	if (force ||
	    refcount_read(&sk->sk_wmem_alloc) < READ_ONCE(sk->sk_sndbuf)) {
		struct sk_buff *skb = alloc_skb(size, priority);

		if (skb) {
			skb_set_owner_w(skb, sk);
			return skb;
		}
	}
	return NULL;
}