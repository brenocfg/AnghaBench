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
typedef  int /*<<< orphan*/  val ;
struct sk_buff {int dummy; } ;
struct msghdr {int dummy; } ;
struct TYPE_2__ {int frag_max_size; } ;

/* Variables and functions */
 TYPE_1__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IP_RECVFRAGSIZE ; 
 int /*<<< orphan*/  SOL_IP ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void ip_cmsg_recv_fragsize(struct msghdr *msg, struct sk_buff *skb)
{
	int val;

	if (IPCB(skb)->frag_max_size == 0)
		return;

	val = IPCB(skb)->frag_max_size;
	put_cmsg(msg, SOL_IP, IP_RECVFRAGSIZE, sizeof(val), &val);
}