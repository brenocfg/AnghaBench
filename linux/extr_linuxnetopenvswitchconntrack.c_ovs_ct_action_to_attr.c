#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_6__ {scalar_t__ mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct ovs_conntrack_info {int /*<<< orphan*/  eventmask; scalar_t__ have_eventmask; TYPE_2__* helper; TYPE_3__ labels; TYPE_3__ mark; TYPE_1__ zone; scalar_t__ force; scalar_t__ commit; } ;
struct nlattr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_NF_CONNTRACK_LABELS ; 
 int /*<<< orphan*/  CONFIG_NF_CONNTRACK_MARK ; 
 int /*<<< orphan*/  CONFIG_NF_CONNTRACK_ZONES ; 
 int EMSGSIZE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OVS_ACTION_ATTR_CT ; 
 int /*<<< orphan*/  OVS_CT_ATTR_COMMIT ; 
 int /*<<< orphan*/  OVS_CT_ATTR_EVENTMASK ; 
 int /*<<< orphan*/  OVS_CT_ATTR_FORCE_COMMIT ; 
 int /*<<< orphan*/  OVS_CT_ATTR_HELPER ; 
 int /*<<< orphan*/  OVS_CT_ATTR_LABELS ; 
 int /*<<< orphan*/  OVS_CT_ATTR_MARK ; 
 int /*<<< orphan*/  OVS_CT_ATTR_ZONE ; 
 scalar_t__ labels_nonzero (scalar_t__*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ovs_ct_action_to_attr(const struct ovs_conntrack_info *ct_info,
			  struct sk_buff *skb)
{
	struct nlattr *start;

	start = nla_nest_start(skb, OVS_ACTION_ATTR_CT);
	if (!start)
		return -EMSGSIZE;

	if (ct_info->commit && nla_put_flag(skb, ct_info->force
					    ? OVS_CT_ATTR_FORCE_COMMIT
					    : OVS_CT_ATTR_COMMIT))
		return -EMSGSIZE;
	if (IS_ENABLED(CONFIG_NF_CONNTRACK_ZONES) &&
	    nla_put_u16(skb, OVS_CT_ATTR_ZONE, ct_info->zone.id))
		return -EMSGSIZE;
	if (IS_ENABLED(CONFIG_NF_CONNTRACK_MARK) && ct_info->mark.mask &&
	    nla_put(skb, OVS_CT_ATTR_MARK, sizeof(ct_info->mark),
		    &ct_info->mark))
		return -EMSGSIZE;
	if (IS_ENABLED(CONFIG_NF_CONNTRACK_LABELS) &&
	    labels_nonzero(&ct_info->labels.mask) &&
	    nla_put(skb, OVS_CT_ATTR_LABELS, sizeof(ct_info->labels),
		    &ct_info->labels))
		return -EMSGSIZE;
	if (ct_info->helper) {
		if (nla_put_string(skb, OVS_CT_ATTR_HELPER,
				   ct_info->helper->name))
			return -EMSGSIZE;
	}
	if (ct_info->have_eventmask &&
	    nla_put_u32(skb, OVS_CT_ATTR_EVENTMASK, ct_info->eventmask))
		return -EMSGSIZE;

#ifdef CONFIG_NF_NAT_NEEDED
	if (ct_info->nat && !ovs_ct_nat_to_attr(ct_info, skb))
		return -EMSGSIZE;
#endif
	nla_nest_end(skb, start);

	return 0;
}