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
struct vport_parms {int /*<<< orphan*/  type; } ;
struct vport_ops {int /*<<< orphan*/  owner; struct vport* (* create ) (struct vport_parms const*) ;} ;
struct vport {int /*<<< orphan*/  hash_node; int /*<<< orphan*/  dp; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  EAGAIN ; 
 struct vport* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct vport*) ; 
 struct hlist_head* hash_bucket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,struct hlist_head*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_dp_get_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_lock () ; 
 int /*<<< orphan*/  ovs_unlock () ; 
 struct vport_ops* ovs_vport_lookup (struct vport_parms const*) ; 
 int /*<<< orphan*/  ovs_vport_name (struct vport*) ; 
 int /*<<< orphan*/  request_module (char*,int /*<<< orphan*/ ) ; 
 struct vport* stub1 (struct vport_parms const*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct vport *ovs_vport_add(const struct vport_parms *parms)
{
	struct vport_ops *ops;
	struct vport *vport;

	ops = ovs_vport_lookup(parms);
	if (ops) {
		struct hlist_head *bucket;

		if (!try_module_get(ops->owner))
			return ERR_PTR(-EAFNOSUPPORT);

		vport = ops->create(parms);
		if (IS_ERR(vport)) {
			module_put(ops->owner);
			return vport;
		}

		bucket = hash_bucket(ovs_dp_get_net(vport->dp),
				     ovs_vport_name(vport));
		hlist_add_head_rcu(&vport->hash_node, bucket);
		return vport;
	}

	/* Unlock to attempt module load and return -EAGAIN if load
	 * was successful as we need to restart the port addition
	 * workflow.
	 */
	ovs_unlock();
	request_module("vport-type-%d", parms->type);
	ovs_lock();

	if (!ovs_vport_lookup(parms))
		return ERR_PTR(-EAFNOSUPPORT);
	else
		return ERR_PTR(-EAGAIN);
}