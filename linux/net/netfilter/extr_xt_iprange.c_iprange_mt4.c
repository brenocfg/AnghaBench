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
struct TYPE_8__ {int /*<<< orphan*/  ip; } ;
struct TYPE_7__ {int /*<<< orphan*/  ip; } ;
struct TYPE_6__ {int /*<<< orphan*/  ip; } ;
struct TYPE_5__ {int /*<<< orphan*/  ip; } ;
struct xt_iprange_mtinfo {int flags; TYPE_4__ dst_max; TYPE_3__ dst_min; TYPE_2__ src_max; TYPE_1__ src_min; } ;
struct xt_action_param {struct xt_iprange_mtinfo* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int IPRANGE_DST ; 
 int IPRANGE_DST_INV ; 
 int IPRANGE_SRC ; 
 int IPRANGE_SRC_INV ; 
 struct iphdr* ip_hdr (struct sk_buff const*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
iprange_mt4(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_iprange_mtinfo *info = par->matchinfo;
	const struct iphdr *iph = ip_hdr(skb);
	bool m;

	if (info->flags & IPRANGE_SRC) {
		m  = ntohl(iph->saddr) < ntohl(info->src_min.ip);
		m |= ntohl(iph->saddr) > ntohl(info->src_max.ip);
		m ^= !!(info->flags & IPRANGE_SRC_INV);
		if (m) {
			pr_debug("src IP %pI4 NOT in range %s%pI4-%pI4\n",
			         &iph->saddr,
			         (info->flags & IPRANGE_SRC_INV) ? "(INV) " : "",
			         &info->src_min.ip,
			         &info->src_max.ip);
			return false;
		}
	}
	if (info->flags & IPRANGE_DST) {
		m  = ntohl(iph->daddr) < ntohl(info->dst_min.ip);
		m |= ntohl(iph->daddr) > ntohl(info->dst_max.ip);
		m ^= !!(info->flags & IPRANGE_DST_INV);
		if (m) {
			pr_debug("dst IP %pI4 NOT in range %s%pI4-%pI4\n",
			         &iph->daddr,
			         (info->flags & IPRANGE_DST_INV) ? "(INV) " : "",
			         &info->dst_min.ip,
			         &info->dst_max.ip);
			return false;
		}
	}
	return true;
}