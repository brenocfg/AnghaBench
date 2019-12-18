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
 int bpf_redirect (scalar_t__,int /*<<< orphan*/ ) ; 

int _redirect_xmit(struct __sk_buff *skb)
{
	return bpf_redirect(skb->ifindex + 1, 0);
}