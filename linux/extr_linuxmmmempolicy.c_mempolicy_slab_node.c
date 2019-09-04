#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct zoneref {int /*<<< orphan*/  zone; } ;
struct zonelist {int dummy; } ;
struct TYPE_4__ {unsigned int preferred_node; int /*<<< orphan*/  nodes; } ;
struct mempolicy {int flags; int mode; TYPE_1__ v; } ;
typedef  enum zone_type { ____Placeholder_zone_type } zone_type ;
struct TYPE_6__ {struct zonelist* node_zonelists; } ;
struct TYPE_5__ {struct mempolicy* mempolicy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  MPOL_BIND 130 
 int MPOL_F_LOCAL ; 
#define  MPOL_INTERLEAVE 129 
#define  MPOL_PREFERRED 128 
 TYPE_3__* NODE_DATA (int) ; 
 size_t ZONELIST_FALLBACK ; 
 TYPE_2__* current ; 
 struct zoneref* first_zones_zonelist (struct zonelist*,int,int /*<<< orphan*/ *) ; 
 int gfp_zone (int /*<<< orphan*/ ) ; 
 scalar_t__ in_interrupt () ; 
 unsigned int interleave_nodes (struct mempolicy*) ; 
 int numa_mem_id () ; 
 unsigned int zone_to_nid (int /*<<< orphan*/ ) ; 

unsigned int mempolicy_slab_node(void)
{
	struct mempolicy *policy;
	int node = numa_mem_id();

	if (in_interrupt())
		return node;

	policy = current->mempolicy;
	if (!policy || policy->flags & MPOL_F_LOCAL)
		return node;

	switch (policy->mode) {
	case MPOL_PREFERRED:
		/*
		 * handled MPOL_F_LOCAL above
		 */
		return policy->v.preferred_node;

	case MPOL_INTERLEAVE:
		return interleave_nodes(policy);

	case MPOL_BIND: {
		struct zoneref *z;

		/*
		 * Follow bind policy behavior and start allocation at the
		 * first node.
		 */
		struct zonelist *zonelist;
		enum zone_type highest_zoneidx = gfp_zone(GFP_KERNEL);
		zonelist = &NODE_DATA(node)->node_zonelists[ZONELIST_FALLBACK];
		z = first_zones_zonelist(zonelist, highest_zoneidx,
							&policy->v.nodes);
		return z->zone ? zone_to_nid(z->zone) : node;
	}

	default:
		BUG();
	}
}