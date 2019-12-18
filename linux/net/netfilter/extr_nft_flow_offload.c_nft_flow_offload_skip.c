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
struct sk_buff {int dummy; } ;
struct ip_options {int /*<<< orphan*/  optlen; } ;
struct TYPE_2__ {struct ip_options opt; } ;

/* Variables and functions */
 TYPE_1__* IPCB (struct sk_buff*) ; 
 int NFPROTO_IPV4 ; 
 scalar_t__ skb_sec_path (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nft_flow_offload_skip(struct sk_buff *skb, int family)
{
	if (skb_sec_path(skb))
		return true;

	if (family == NFPROTO_IPV4) {
		const struct ip_options *opt;

		opt = &(IPCB(skb)->opt);

		if (unlikely(opt->optlen))
			return true;
	}

	return false;
}