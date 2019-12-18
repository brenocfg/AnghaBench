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
struct vport_parms {int /*<<< orphan*/  upcall_portids; int /*<<< orphan*/  port_no; int /*<<< orphan*/  dp; } ;
struct vport_ops {int dummy; } ;
struct vport {int /*<<< orphan*/  dp_hash_node; struct vport_ops const* ops; int /*<<< orphan*/  port_no; int /*<<< orphan*/  dp; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct vport* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VPORT_ALIGN ; 
 int /*<<< orphan*/  kfree (struct vport*) ; 
 struct vport* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ ovs_vport_set_upcall_portids (struct vport*,int /*<<< orphan*/ ) ; 

struct vport *ovs_vport_alloc(int priv_size, const struct vport_ops *ops,
			  const struct vport_parms *parms)
{
	struct vport *vport;
	size_t alloc_size;

	alloc_size = sizeof(struct vport);
	if (priv_size) {
		alloc_size = ALIGN(alloc_size, VPORT_ALIGN);
		alloc_size += priv_size;
	}

	vport = kzalloc(alloc_size, GFP_KERNEL);
	if (!vport)
		return ERR_PTR(-ENOMEM);

	vport->dp = parms->dp;
	vport->port_no = parms->port_no;
	vport->ops = ops;
	INIT_HLIST_NODE(&vport->dp_hash_node);

	if (ovs_vport_set_upcall_portids(vport, parms->upcall_portids)) {
		kfree(vport);
		return ERR_PTR(-EINVAL);
	}

	return vport;
}