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
struct devlink_resource_size_params {int /*<<< orphan*/  unit; int /*<<< orphan*/  size_min; int /*<<< orphan*/  size_max; int /*<<< orphan*/  size_granularity; } ;
struct devlink_resource {struct devlink_resource_size_params size_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_PAD ; 
 int /*<<< orphan*/  DEVLINK_ATTR_RESOURCE_SIZE_GRAN ; 
 int /*<<< orphan*/  DEVLINK_ATTR_RESOURCE_SIZE_MAX ; 
 int /*<<< orphan*/  DEVLINK_ATTR_RESOURCE_SIZE_MIN ; 
 int /*<<< orphan*/  DEVLINK_ATTR_RESOURCE_UNIT ; 
 int EMSGSIZE ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
devlink_resource_size_params_put(struct devlink_resource *resource,
				 struct sk_buff *skb)
{
	struct devlink_resource_size_params *size_params;

	size_params = &resource->size_params;
	if (nla_put_u64_64bit(skb, DEVLINK_ATTR_RESOURCE_SIZE_GRAN,
			      size_params->size_granularity, DEVLINK_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, DEVLINK_ATTR_RESOURCE_SIZE_MAX,
			      size_params->size_max, DEVLINK_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, DEVLINK_ATTR_RESOURCE_SIZE_MIN,
			      size_params->size_min, DEVLINK_ATTR_PAD) ||
	    nla_put_u8(skb, DEVLINK_ATTR_RESOURCE_UNIT, size_params->unit))
		return -EMSGSIZE;
	return 0;
}