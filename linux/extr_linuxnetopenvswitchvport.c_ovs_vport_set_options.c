#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vport {TYPE_1__* ops; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {int (* set_options ) (struct vport*,struct nlattr*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct vport*,struct nlattr*) ; 

int ovs_vport_set_options(struct vport *vport, struct nlattr *options)
{
	if (!vport->ops->set_options)
		return -EOPNOTSUPP;
	return vport->ops->set_options(vport, options);
}