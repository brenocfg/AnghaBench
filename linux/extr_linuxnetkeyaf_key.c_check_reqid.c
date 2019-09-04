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
typedef  scalar_t__ u32 ;
struct xfrm_policy {int xfrm_nr; TYPE_1__* xfrm_vec; } ;
struct TYPE_2__ {scalar_t__ reqid; } ;

/* Variables and functions */
 int EEXIST ; 

__attribute__((used)) static int check_reqid(struct xfrm_policy *xp, int dir, int count, void *ptr)
{
	int i;
	u32 reqid = *(u32*)ptr;

	for (i=0; i<xp->xfrm_nr; i++) {
		if (xp->xfrm_vec[i].reqid == reqid)
			return -EEXIST;
	}
	return 0;
}