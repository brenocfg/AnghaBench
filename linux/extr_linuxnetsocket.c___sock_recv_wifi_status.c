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
struct sk_buff {int wifi_acked; int /*<<< orphan*/  wifi_acked_valid; } ;
struct msghdr {int dummy; } ;
typedef  int /*<<< orphan*/  ack ;

/* Variables and functions */
 int /*<<< orphan*/  SCM_WIFI_STATUS ; 
 int /*<<< orphan*/  SOCK_WIFI_STATUS ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

void __sock_recv_wifi_status(struct msghdr *msg, struct sock *sk,
	struct sk_buff *skb)
{
	int ack;

	if (!sock_flag(sk, SOCK_WIFI_STATUS))
		return;
	if (!skb->wifi_acked_valid)
		return;

	ack = skb->wifi_acked;

	put_cmsg(msg, SOL_SOCKET, SCM_WIFI_STATUS, sizeof(ack), &ack);
}