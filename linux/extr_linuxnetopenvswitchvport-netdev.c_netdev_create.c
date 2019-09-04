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
struct vport_parms {int /*<<< orphan*/  name; } ;
struct vport {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct vport*) ; 
 struct vport* ovs_netdev_link (struct vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_netdev_vport_ops ; 
 struct vport* ovs_vport_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vport_parms const*) ; 

__attribute__((used)) static struct vport *netdev_create(const struct vport_parms *parms)
{
	struct vport *vport;

	vport = ovs_vport_alloc(0, &ovs_netdev_vport_ops, parms);
	if (IS_ERR(vport))
		return vport;

	return ovs_netdev_link(vport, parms->name);
}