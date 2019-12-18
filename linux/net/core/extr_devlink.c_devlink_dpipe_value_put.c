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
struct devlink_dpipe_value {int /*<<< orphan*/  mapping_value; scalar_t__ mapping_valid; scalar_t__ mask; int /*<<< orphan*/  value_size; scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_VALUE ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_VALUE_MAPPING ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_VALUE_MASK ; 
 int EMSGSIZE ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_dpipe_value_put(struct sk_buff *skb,
				   struct devlink_dpipe_value *value)
{
	if (nla_put(skb, DEVLINK_ATTR_DPIPE_VALUE,
		    value->value_size, value->value))
		return -EMSGSIZE;
	if (value->mask)
		if (nla_put(skb, DEVLINK_ATTR_DPIPE_VALUE_MASK,
			    value->value_size, value->mask))
			return -EMSGSIZE;
	if (value->mapping_valid)
		if (nla_put_u32(skb, DEVLINK_ATTR_DPIPE_VALUE_MAPPING,
				value->mapping_value))
			return -EMSGSIZE;
	return 0;
}