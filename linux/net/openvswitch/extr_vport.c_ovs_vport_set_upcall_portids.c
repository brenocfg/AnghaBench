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
typedef  int /*<<< orphan*/  u32 ;
struct vport_portids {int n_ids; int /*<<< orphan*/  ids; int /*<<< orphan*/  rn_ids; } ;
struct vport {int /*<<< orphan*/  upcall_portids; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree_rcu (struct vport_portids*,int /*<<< orphan*/ ) ; 
 struct vport_portids* kmalloc (int,int /*<<< orphan*/ ) ; 
 int nla_len (struct nlattr const*) ; 
 int /*<<< orphan*/  nla_memcpy (int /*<<< orphan*/ ,struct nlattr const*,int) ; 
 struct vport_portids* ovsl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct vport_portids*) ; 
 int /*<<< orphan*/  reciprocal_value (int) ; 

int ovs_vport_set_upcall_portids(struct vport *vport, const struct nlattr *ids)
{
	struct vport_portids *old, *vport_portids;

	if (!nla_len(ids) || nla_len(ids) % sizeof(u32))
		return -EINVAL;

	old = ovsl_dereference(vport->upcall_portids);

	vport_portids = kmalloc(sizeof(*vport_portids) + nla_len(ids),
				GFP_KERNEL);
	if (!vport_portids)
		return -ENOMEM;

	vport_portids->n_ids = nla_len(ids) / sizeof(u32);
	vport_portids->rn_ids = reciprocal_value(vport_portids->n_ids);
	nla_memcpy(vport_portids->ids, ids, nla_len(ids));

	rcu_assign_pointer(vport->upcall_portids, vport_portids);

	if (old)
		kfree_rcu(old, rcu);
	return 0;
}