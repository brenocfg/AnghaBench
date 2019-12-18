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
struct tcf_proto_ops {int /*<<< orphan*/  owner; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOENT ; 
 struct tcf_proto_ops const* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 struct tcf_proto_ops* __tcf_proto_lookup_ops (char const*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_module (char*,char const*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static const struct tcf_proto_ops *
tcf_proto_lookup_ops(const char *kind, bool rtnl_held,
		     struct netlink_ext_ack *extack)
{
	const struct tcf_proto_ops *ops;

	ops = __tcf_proto_lookup_ops(kind);
	if (ops)
		return ops;
#ifdef CONFIG_MODULES
	if (rtnl_held)
		rtnl_unlock();
	request_module("cls_%s", kind);
	if (rtnl_held)
		rtnl_lock();
	ops = __tcf_proto_lookup_ops(kind);
	/* We dropped the RTNL semaphore in order to perform
	 * the module load. So, even if we succeeded in loading
	 * the module we have to replay the request. We indicate
	 * this using -EAGAIN.
	 */
	if (ops) {
		module_put(ops->owner);
		return ERR_PTR(-EAGAIN);
	}
#endif
	NL_SET_ERR_MSG(extack, "TC classifier not found");
	return ERR_PTR(-ENOENT);
}