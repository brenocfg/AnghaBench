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
struct devlink_dpipe_value {int /*<<< orphan*/  action; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 scalar_t__ devlink_dpipe_action_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ devlink_dpipe_value_put (struct sk_buff*,struct devlink_dpipe_value*) ; 

__attribute__((used)) static int devlink_dpipe_action_value_put(struct sk_buff *skb,
					  struct devlink_dpipe_value *value)
{
	if (!value->action)
		return -EINVAL;
	if (devlink_dpipe_action_put(skb, value->action))
		return -EMSGSIZE;
	if (devlink_dpipe_value_put(skb, value))
		return -EMSGSIZE;
	return 0;
}