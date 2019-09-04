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
struct vport {int dummy; } ;
struct datapath {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVSP_LOCAL ; 
 char const* ovs_vport_name (struct vport*) ; 
 struct vport* ovs_vport_ovsl_rcu (struct datapath const*,int /*<<< orphan*/ ) ; 

const char *ovs_dp_name(const struct datapath *dp)
{
	struct vport *vport = ovs_vport_ovsl_rcu(dp, OVSP_LOCAL);
	return ovs_vport_name(vport);
}