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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct devlink_trap_item {int /*<<< orphan*/  stats; TYPE_2__* trap; int /*<<< orphan*/  action; struct devlink_trap_group_item* group_item; } ;
struct devlink_trap_group_item {TYPE_1__* group; } ;
struct devlink {int dummy; } ;
typedef  enum devlink_command { ____Placeholder_devlink_command } devlink_command ;
struct TYPE_4__ {scalar_t__ generic; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_TRAP_ACTION ; 
 int /*<<< orphan*/  DEVLINK_ATTR_TRAP_GENERIC ; 
 int /*<<< orphan*/  DEVLINK_ATTR_TRAP_GROUP_NAME ; 
 int /*<<< orphan*/  DEVLINK_ATTR_TRAP_NAME ; 
 int /*<<< orphan*/  DEVLINK_ATTR_TRAP_TYPE ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  devlink_nl_family ; 
 scalar_t__ devlink_nl_put_handle (struct sk_buff*,struct devlink*) ; 
 int devlink_trap_metadata_put (struct sk_buff*,TYPE_2__*) ; 
 int devlink_trap_stats_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_trap_fill(struct sk_buff *msg, struct devlink *devlink,
				const struct devlink_trap_item *trap_item,
				enum devlink_command cmd, u32 portid, u32 seq,
				int flags)
{
	struct devlink_trap_group_item *group_item = trap_item->group_item;
	void *hdr;
	int err;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	if (!hdr)
		return -EMSGSIZE;

	if (devlink_nl_put_handle(msg, devlink))
		goto nla_put_failure;

	if (nla_put_string(msg, DEVLINK_ATTR_TRAP_GROUP_NAME,
			   group_item->group->name))
		goto nla_put_failure;

	if (nla_put_string(msg, DEVLINK_ATTR_TRAP_NAME, trap_item->trap->name))
		goto nla_put_failure;

	if (nla_put_u8(msg, DEVLINK_ATTR_TRAP_TYPE, trap_item->trap->type))
		goto nla_put_failure;

	if (trap_item->trap->generic &&
	    nla_put_flag(msg, DEVLINK_ATTR_TRAP_GENERIC))
		goto nla_put_failure;

	if (nla_put_u8(msg, DEVLINK_ATTR_TRAP_ACTION, trap_item->action))
		goto nla_put_failure;

	err = devlink_trap_metadata_put(msg, trap_item->trap);
	if (err)
		goto nla_put_failure;

	err = devlink_trap_stats_put(msg, trap_item->stats);
	if (err)
		goto nla_put_failure;

	genlmsg_end(msg, hdr);

	return 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}