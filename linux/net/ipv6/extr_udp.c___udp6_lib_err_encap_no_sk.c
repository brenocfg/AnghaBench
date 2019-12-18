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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct ip6_tnl_encap_ops {int (* err_handler ) (struct sk_buff*,struct inet6_skb_parm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
struct inet6_skb_parm {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOENT ; 
 int MAX_IPTUN_ENCAP_OPS ; 
 int /*<<< orphan*/ * ip6tun_encaps ; 
 struct ip6_tnl_encap_ops* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __udp6_lib_err_encap_no_sk(struct sk_buff *skb,
				      struct inet6_skb_parm *opt,
				      u8 type, u8 code, int offset, __be32 info)
{
	int i;

	for (i = 0; i < MAX_IPTUN_ENCAP_OPS; i++) {
		int (*handler)(struct sk_buff *skb, struct inet6_skb_parm *opt,
			       u8 type, u8 code, int offset, __be32 info);
		const struct ip6_tnl_encap_ops *encap;

		encap = rcu_dereference(ip6tun_encaps[i]);
		if (!encap)
			continue;
		handler = encap->err_handler;
		if (handler && !handler(skb, opt, type, code, offset, info))
			return 0;
	}

	return -ENOENT;
}