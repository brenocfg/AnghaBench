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
typedef  int /*<<< orphan*/  u32 ;
struct rpmsg_endpoint {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* trysendto ) (struct rpmsg_endpoint*,void*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ WARN_ON (int) ; 
 int stub1 (struct rpmsg_endpoint*,void*,int,int /*<<< orphan*/ ) ; 

int rpmsg_trysendto(struct rpmsg_endpoint *ept, void *data, int len, u32 dst)
{
	if (WARN_ON(!ept))
		return -EINVAL;
	if (!ept->ops->trysendto)
		return -ENXIO;

	return ept->ops->trysendto(ept, data, len, dst);
}