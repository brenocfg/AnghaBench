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
typedef  int /*<<< orphan*/  u8 ;
struct xt_action_param {struct ipt_ttl_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct ipt_ttl_info {int mode; int /*<<< orphan*/  const ttl; } ;
struct TYPE_2__ {int /*<<< orphan*/  ttl; } ;

/* Variables and functions */
#define  IPT_TTL_EQ 131 
#define  IPT_TTL_GT 130 
#define  IPT_TTL_LT 129 
#define  IPT_TTL_NE 128 
 TYPE_1__* ip_hdr (struct sk_buff const*) ; 

__attribute__((used)) static bool ttl_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct ipt_ttl_info *info = par->matchinfo;
	const u8 ttl = ip_hdr(skb)->ttl;

	switch (info->mode) {
	case IPT_TTL_EQ:
		return ttl == info->ttl;
	case IPT_TTL_NE:
		return ttl != info->ttl;
	case IPT_TTL_LT:
		return ttl < info->ttl;
	case IPT_TTL_GT:
		return ttl > info->ttl;
	}

	return false;
}