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
struct genl_info {TYPE_1__* nlhdr; } ;
struct TYPE_2__ {int nlmsg_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int NLM_F_CREATE ; 
 int NLM_F_EXCL ; 
 int ieee802154_nl_llsec_change (struct sk_buff*,struct genl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llsec_add_key ; 

int ieee802154_llsec_add_key(struct sk_buff *skb, struct genl_info *info)
{
	if ((info->nlhdr->nlmsg_flags & (NLM_F_CREATE | NLM_F_EXCL)) !=
	    (NLM_F_CREATE | NLM_F_EXCL))
		return -EINVAL;

	return ieee802154_nl_llsec_change(skb, info, llsec_add_key);
}