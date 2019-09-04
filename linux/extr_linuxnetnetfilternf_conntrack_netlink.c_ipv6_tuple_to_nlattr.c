#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  in6; } ;
struct TYPE_8__ {TYPE_3__ u3; } ;
struct TYPE_5__ {int /*<<< orphan*/  in6; } ;
struct TYPE_6__ {TYPE_1__ u3; } ;
struct nf_conntrack_tuple {TYPE_4__ dst; TYPE_2__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTA_IP_V6_DST ; 
 int /*<<< orphan*/  CTA_IP_V6_SRC ; 
 int EMSGSIZE ; 
 scalar_t__ nla_put_in6_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipv6_tuple_to_nlattr(struct sk_buff *skb,
				const struct nf_conntrack_tuple *tuple)
{
	if (nla_put_in6_addr(skb, CTA_IP_V6_SRC, &tuple->src.u3.in6) ||
	    nla_put_in6_addr(skb, CTA_IP_V6_DST, &tuple->dst.u3.in6))
		return -EMSGSIZE;
	return 0;
}