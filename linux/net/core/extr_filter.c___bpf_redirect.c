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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int __bpf_redirect_common (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ) ; 
 int __bpf_redirect_no_mac (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ dev_is_mac_header_xmit (struct net_device*) ; 

__attribute__((used)) static int __bpf_redirect(struct sk_buff *skb, struct net_device *dev,
			  u32 flags)
{
	if (dev_is_mac_header_xmit(dev))
		return __bpf_redirect_common(skb, dev, flags);
	else
		return __bpf_redirect_no_mac(skb, dev, flags);
}