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
struct net_device {int dummy; } ;
struct neighbour {scalar_t__ type; TYPE_2__* ops; int /*<<< orphan*/  output; int /*<<< orphan*/  nud_state; TYPE_1__* tbl; } ;
struct atmarp_entry {scalar_t__ expires; int /*<<< orphan*/ * vccs; struct neighbour* neigh; } ;
struct TYPE_4__ {int /*<<< orphan*/  output; } ;
struct TYPE_3__ {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EINVAL ; 
 int /*<<< orphan*/  NUD_NONE ; 
 scalar_t__ RTN_UNICAST ; 
 TYPE_2__ clip_neigh_ops ; 
 scalar_t__ jiffies ; 
 struct atmarp_entry* neighbour_priv (struct neighbour*) ; 

__attribute__((used)) static int clip_constructor(struct net_device *dev, struct neighbour *neigh)
{
	struct atmarp_entry *entry = neighbour_priv(neigh);

	if (neigh->tbl->family != AF_INET)
		return -EINVAL;

	if (neigh->type != RTN_UNICAST)
		return -EINVAL;

	neigh->nud_state = NUD_NONE;
	neigh->ops = &clip_neigh_ops;
	neigh->output = neigh->ops->output;
	entry->neigh = neigh;
	entry->vccs = NULL;
	entry->expires = jiffies - 1;

	return 0;
}