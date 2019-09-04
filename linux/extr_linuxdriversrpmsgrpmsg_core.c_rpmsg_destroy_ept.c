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
struct rpmsg_endpoint {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy_ept ) (struct rpmsg_endpoint*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rpmsg_endpoint*) ; 

void rpmsg_destroy_ept(struct rpmsg_endpoint *ept)
{
	if (ept)
		ept->ops->destroy_ept(ept);
}