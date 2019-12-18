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
struct sk_psock {int /*<<< orphan*/  sk; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int sk_psock_skb_ingress (struct sk_psock*,struct sk_buff*) ; 
 int skb_send_sock_locked (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sk_psock_handle_skb(struct sk_psock *psock, struct sk_buff *skb,
			       u32 off, u32 len, bool ingress)
{
	if (ingress)
		return sk_psock_skb_ingress(psock, skb);
	else
		return skb_send_sock_locked(psock->sk, skb, off, len);
}