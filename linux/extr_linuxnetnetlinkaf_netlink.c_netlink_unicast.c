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
struct sock {int dummy; } ;
struct sk_buff {int len; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sock*) ; 
 int PTR_ERR (struct sock*) ; 
 int /*<<< orphan*/  gfp_any () ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int netlink_attachskb (struct sock*,struct sk_buff*,long*,struct sock*) ; 
 struct sock* netlink_getsockbyportid (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ netlink_is_kernel (struct sock*) ; 
 int netlink_sendskb (struct sock*,struct sk_buff*) ; 
 struct sk_buff* netlink_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int netlink_unicast_kernel (struct sock*,struct sk_buff*,struct sock*) ; 
 scalar_t__ sk_filter (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 long sock_sndtimeo (struct sock*,int) ; 

int netlink_unicast(struct sock *ssk, struct sk_buff *skb,
		    u32 portid, int nonblock)
{
	struct sock *sk;
	int err;
	long timeo;

	skb = netlink_trim(skb, gfp_any());

	timeo = sock_sndtimeo(ssk, nonblock);
retry:
	sk = netlink_getsockbyportid(ssk, portid);
	if (IS_ERR(sk)) {
		kfree_skb(skb);
		return PTR_ERR(sk);
	}
	if (netlink_is_kernel(sk))
		return netlink_unicast_kernel(sk, skb, ssk);

	if (sk_filter(sk, skb)) {
		err = skb->len;
		kfree_skb(skb);
		sock_put(sk);
		return err;
	}

	err = netlink_attachskb(sk, skb, &timeo, ssk);
	if (err == 1)
		goto retry;
	if (err)
		return err;

	return netlink_sendskb(sk, skb);
}