#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ v1; } ;
struct xt_string_info {int /*<<< orphan*/  config; int /*<<< orphan*/  to_offset; int /*<<< orphan*/  from_offset; TYPE_2__ u; } ;
struct xt_action_param {struct xt_string_info* matchinfo; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ UINT_MAX ; 
 int XT_STRING_FLAG_INVERT ; 
 scalar_t__ skb_find_text (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
string_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_string_info *conf = par->matchinfo;
	bool invert;

	invert = conf->u.v1.flags & XT_STRING_FLAG_INVERT;

	return (skb_find_text((struct sk_buff *)skb, conf->from_offset,
			     conf->to_offset, conf->config)
			     != UINT_MAX) ^ invert;
}