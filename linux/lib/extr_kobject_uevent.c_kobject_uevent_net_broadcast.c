#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net {TYPE_3__* uevent_sock; } ;
struct kobject {TYPE_2__* ktype; struct kobject* parent; TYPE_1__* kset; } ;
struct kobj_uevent_env {int dummy; } ;
struct kobj_ns_type_operations {scalar_t__ type; scalar_t__ netlink_ns; } ;
struct TYPE_6__ {int /*<<< orphan*/  sk; } ;
struct TYPE_5__ {struct net* (* namespace ) (struct kobject*) ;} ;
struct TYPE_4__ {struct kobject kobj; } ;

/* Variables and functions */
 scalar_t__ KOBJ_NS_TYPE_NET ; 
 struct kobj_ns_type_operations* kobj_ns_ops (struct kobject*) ; 
 struct net* stub1 (struct kobject*) ; 
 int uevent_net_broadcast_tagged (int /*<<< orphan*/ ,struct kobj_uevent_env*,char const*,char const*) ; 
 int uevent_net_broadcast_untagged (struct kobj_uevent_env*,char const*,char const*) ; 

__attribute__((used)) static int kobject_uevent_net_broadcast(struct kobject *kobj,
					struct kobj_uevent_env *env,
					const char *action_string,
					const char *devpath)
{
	int ret = 0;

#ifdef CONFIG_NET
	const struct kobj_ns_type_operations *ops;
	const struct net *net = NULL;

	ops = kobj_ns_ops(kobj);
	if (!ops && kobj->kset) {
		struct kobject *ksobj = &kobj->kset->kobj;

		if (ksobj->parent != NULL)
			ops = kobj_ns_ops(ksobj->parent);
	}

	/* kobjects currently only carry network namespace tags and they
	 * are the only tag relevant here since we want to decide which
	 * network namespaces to broadcast the uevent into.
	 */
	if (ops && ops->netlink_ns && kobj->ktype->namespace)
		if (ops->type == KOBJ_NS_TYPE_NET)
			net = kobj->ktype->namespace(kobj);

	if (!net)
		ret = uevent_net_broadcast_untagged(env, action_string,
						    devpath);
	else
		ret = uevent_net_broadcast_tagged(net->uevent_sock->sk, env,
						  action_string, devpath);
#endif

	return ret;
}