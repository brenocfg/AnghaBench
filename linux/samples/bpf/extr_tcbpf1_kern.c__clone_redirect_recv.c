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
struct __sk_buff {scalar_t__ ifindex; } ;

/* Variables and functions */
 int TC_ACT_SHOT ; 
 int /*<<< orphan*/  bpf_clone_redirect (struct __sk_buff*,scalar_t__,int) ; 

int _clone_redirect_recv(struct __sk_buff *skb)
{
	bpf_clone_redirect(skb, skb->ifindex + 1, 1);
	return TC_ACT_SHOT;
}