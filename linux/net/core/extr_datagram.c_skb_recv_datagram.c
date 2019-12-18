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
 unsigned int MSG_DONTWAIT ; 
 struct sk_buff* __skb_recv_datagram (struct sock*,unsigned int,int /*<<< orphan*/ *,int*,int*) ; 

struct sk_buff *skb_recv_datagram(struct sock *sk, unsigned int flags,
				  int noblock, int *err)
{
	int off = 0;

	return __skb_recv_datagram(sk, flags | (noblock ? MSG_DONTWAIT : 0),
				   NULL, &off, err);
}