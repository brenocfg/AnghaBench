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
struct devlink_trap {int metadata_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_TRAP_METADATA ; 
 int /*<<< orphan*/  DEVLINK_ATTR_TRAP_METADATA_TYPE_IN_PORT ; 
 int DEVLINK_TRAP_METADATA_TYPE_F_IN_PORT ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_trap_metadata_put(struct sk_buff *msg,
				     const struct devlink_trap *trap)
{
	struct nlattr *attr;

	attr = nla_nest_start(msg, DEVLINK_ATTR_TRAP_METADATA);
	if (!attr)
		return -EMSGSIZE;

	if ((trap->metadata_cap & DEVLINK_TRAP_METADATA_TYPE_F_IN_PORT) &&
	    nla_put_flag(msg, DEVLINK_ATTR_TRAP_METADATA_TYPE_IN_PORT))
		goto nla_put_failure;

	nla_nest_end(msg, attr);

	return 0;

nla_put_failure:
	nla_nest_cancel(msg, attr);
	return -EMSGSIZE;
}