#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int* policy_count; TYPE_1__* policy_bydst; } ;
struct net {TYPE_2__ xfrm; } ;
struct TYPE_3__ {unsigned int hmask; } ;

/* Variables and functions */
 unsigned int xfrm_policy_hashmax ; 

__attribute__((used)) static inline int xfrm_bydst_should_resize(struct net *net, int dir, int *total)
{
	unsigned int cnt = net->xfrm.policy_count[dir];
	unsigned int hmask = net->xfrm.policy_bydst[dir].hmask;

	if (total)
		*total += cnt;

	if ((hmask + 1) < xfrm_policy_hashmax &&
	    cnt > hmask)
		return 1;

	return 0;
}