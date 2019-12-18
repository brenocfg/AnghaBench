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
struct TYPE_2__ {scalar_t__ state_hmask; scalar_t__ state_num; int /*<<< orphan*/  state_hash_work; } ;
struct net {TYPE_1__ xfrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ xfrm_state_hashmax ; 

__attribute__((used)) static void xfrm_hash_grow_check(struct net *net, int have_hash_collision)
{
	if (have_hash_collision &&
	    (net->xfrm.state_hmask + 1) < xfrm_state_hashmax &&
	    net->xfrm.state_num > net->xfrm.state_hmask)
		schedule_work(&net->xfrm.state_hash_work);
}