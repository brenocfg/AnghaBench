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
struct devlink_dpipe_header {int /*<<< orphan*/  global; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_HEADER ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_HEADER_FIELDS ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_HEADER_GLOBAL ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_HEADER_ID ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_HEADER_NAME ; 
 int EMSGSIZE ; 
 int devlink_dpipe_fields_put (struct sk_buff*,struct devlink_dpipe_header*) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_dpipe_header_put(struct sk_buff *skb,
				    struct devlink_dpipe_header *header)
{
	struct nlattr *fields_attr, *header_attr;
	int err;

	header_attr = nla_nest_start_noflag(skb, DEVLINK_ATTR_DPIPE_HEADER);
	if (!header_attr)
		return -EMSGSIZE;

	if (nla_put_string(skb, DEVLINK_ATTR_DPIPE_HEADER_NAME, header->name) ||
	    nla_put_u32(skb, DEVLINK_ATTR_DPIPE_HEADER_ID, header->id) ||
	    nla_put_u8(skb, DEVLINK_ATTR_DPIPE_HEADER_GLOBAL, header->global))
		goto nla_put_failure;

	fields_attr = nla_nest_start_noflag(skb,
					    DEVLINK_ATTR_DPIPE_HEADER_FIELDS);
	if (!fields_attr)
		goto nla_put_failure;

	err = devlink_dpipe_fields_put(skb, header);
	if (err) {
		nla_nest_cancel(skb, fields_attr);
		goto nla_put_failure;
	}
	nla_nest_end(skb, fields_attr);
	nla_nest_end(skb, header_attr);
	return 0;

nla_put_failure:
	err = -EMSGSIZE;
	nla_nest_cancel(skb, header_attr);
	return err;
}