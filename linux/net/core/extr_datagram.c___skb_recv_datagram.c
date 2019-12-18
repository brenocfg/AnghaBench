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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 unsigned int MSG_DONTWAIT ; 
 struct sk_buff* __skb_try_recv_datagram (struct sock*,unsigned int,void (*) (struct sock*,struct sk_buff*),int*,int*,struct sk_buff**) ; 
 int /*<<< orphan*/  __skb_wait_for_more_packets (struct sock*,int*,long*,struct sk_buff*) ; 
 long sock_rcvtimeo (struct sock*,unsigned int) ; 

struct sk_buff *__skb_recv_datagram(struct sock *sk, unsigned int flags,
				    void (*destructor)(struct sock *sk,
						       struct sk_buff *skb),
				    int *off, int *err)
{
	struct sk_buff *skb, *last;
	long timeo;

	timeo = sock_rcvtimeo(sk, flags & MSG_DONTWAIT);

	do {
		skb = __skb_try_recv_datagram(sk, flags, destructor, off, err,
					      &last);
		if (skb)
			return skb;

		if (*err != -EAGAIN)
			break;
	} while (timeo &&
		!__skb_wait_for_more_packets(sk, err, &timeo, last));

	return NULL;
}