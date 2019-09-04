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
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int skb_send_sock_locked (struct sock*,struct sk_buff*,int,int) ; 

int skb_send_sock(struct sock *sk, struct sk_buff *skb, int offset, int len)
{
	int ret = 0;

	lock_sock(sk);
	ret = skb_send_sock_locked(sk, skb, offset, len);
	release_sock(sk);

	return ret;
}