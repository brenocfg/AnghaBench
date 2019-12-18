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
struct tcf_proto_ops {int flags; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tcf_proto_ops const*) ; 
 int TCF_PROTO_OPS_DOIT_UNLOCKED ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 struct tcf_proto_ops* tcf_proto_lookup_ops (char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool tcf_proto_is_unlocked(const char *kind)
{
	const struct tcf_proto_ops *ops;
	bool ret;

	if (strlen(kind) == 0)
		return false;

	ops = tcf_proto_lookup_ops(kind, false, NULL);
	/* On error return false to take rtnl lock. Proto lookup/create
	 * functions will perform lookup again and properly handle errors.
	 */
	if (IS_ERR(ops))
		return false;

	ret = !!(ops->flags & TCF_PROTO_OPS_DOIT_UNLOCKED);
	module_put(ops->owner);
	return ret;
}