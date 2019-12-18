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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct devlink_dpipe_header {int /*<<< orphan*/  global; int /*<<< orphan*/  id; struct devlink_dpipe_field* fields; } ;
struct devlink_dpipe_field {int /*<<< orphan*/  id; } ;
struct devlink_dpipe_action {size_t field_id; int /*<<< orphan*/  header_index; int /*<<< orphan*/  type; struct devlink_dpipe_header* header; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_ACTION ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_ACTION_TYPE ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_FIELD_ID ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_HEADER_GLOBAL ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_HEADER_ID ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_HEADER_INDEX ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int devlink_dpipe_action_put(struct sk_buff *skb,
			     struct devlink_dpipe_action *action)
{
	struct devlink_dpipe_header *header = action->header;
	struct devlink_dpipe_field *field = &header->fields[action->field_id];
	struct nlattr *action_attr;

	action_attr = nla_nest_start_noflag(skb, DEVLINK_ATTR_DPIPE_ACTION);
	if (!action_attr)
		return -EMSGSIZE;

	if (nla_put_u32(skb, DEVLINK_ATTR_DPIPE_ACTION_TYPE, action->type) ||
	    nla_put_u32(skb, DEVLINK_ATTR_DPIPE_HEADER_INDEX, action->header_index) ||
	    nla_put_u32(skb, DEVLINK_ATTR_DPIPE_HEADER_ID, header->id) ||
	    nla_put_u32(skb, DEVLINK_ATTR_DPIPE_FIELD_ID, field->id) ||
	    nla_put_u8(skb, DEVLINK_ATTR_DPIPE_HEADER_GLOBAL, header->global))
		goto nla_put_failure;

	nla_nest_end(skb, action_attr);
	return 0;

nla_put_failure:
	nla_nest_cancel(skb, action_attr);
	return -EMSGSIZE;
}