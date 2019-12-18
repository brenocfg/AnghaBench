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
struct net_device {int dummy; } ;
struct lowpan_iphc_ctx {int /*<<< orphan*/  plen; int /*<<< orphan*/  pfx; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int ipv6_addr_equal (struct in6_addr*,struct in6_addr const*) ; 
 int /*<<< orphan*/  ipv6_addr_prefix_copy (struct in6_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lowpan_iphc_uncompress_lladdr (struct net_device const*,struct in6_addr*,void const*) ; 

__attribute__((used)) static bool lowpan_iphc_addr_equal(const struct net_device *dev,
				   const struct lowpan_iphc_ctx *ctx,
				   const struct in6_addr *ipaddr,
				   const void *lladdr)
{
	struct in6_addr tmp = {};

	lowpan_iphc_uncompress_lladdr(dev, &tmp, lladdr);

	if (ctx)
		ipv6_addr_prefix_copy(&tmp, &ctx->pfx, ctx->plen);

	return ipv6_addr_equal(&tmp, ipaddr);
}