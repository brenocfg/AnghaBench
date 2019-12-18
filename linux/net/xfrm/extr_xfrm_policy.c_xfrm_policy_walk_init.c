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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int dead; int /*<<< orphan*/  all; } ;
struct xfrm_policy_walk {scalar_t__ seq; int /*<<< orphan*/  type; TYPE_1__ walk; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

void xfrm_policy_walk_init(struct xfrm_policy_walk *walk, u8 type)
{
	INIT_LIST_HEAD(&walk->walk.all);
	walk->walk.dead = 1;
	walk->type = type;
	walk->seq = 0;
}