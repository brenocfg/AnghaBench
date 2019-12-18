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
struct devlink_dpipe_header {int fields_count; struct devlink_dpipe_field* fields; } ;
struct devlink_dpipe_field {int /*<<< orphan*/  mapping_type; int /*<<< orphan*/  bitwidth; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_FIELD ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_FIELD_BITWIDTH ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_FIELD_ID ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_FIELD_MAPPING_TYPE ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_FIELD_NAME ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_dpipe_fields_put(struct sk_buff *skb,
				    const struct devlink_dpipe_header *header)
{
	struct devlink_dpipe_field *field;
	struct nlattr *field_attr;
	int i;

	for (i = 0; i < header->fields_count; i++) {
		field = &header->fields[i];
		field_attr = nla_nest_start_noflag(skb,
						   DEVLINK_ATTR_DPIPE_FIELD);
		if (!field_attr)
			return -EMSGSIZE;
		if (nla_put_string(skb, DEVLINK_ATTR_DPIPE_FIELD_NAME, field->name) ||
		    nla_put_u32(skb, DEVLINK_ATTR_DPIPE_FIELD_ID, field->id) ||
		    nla_put_u32(skb, DEVLINK_ATTR_DPIPE_FIELD_BITWIDTH, field->bitwidth) ||
		    nla_put_u32(skb, DEVLINK_ATTR_DPIPE_FIELD_MAPPING_TYPE, field->mapping_type))
			goto nla_put_failure;
		nla_nest_end(skb, field_attr);
	}
	return 0;

nla_put_failure:
	nla_nest_cancel(skb, field_attr);
	return -EMSGSIZE;
}