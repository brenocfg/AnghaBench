#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* join_rel; } ;
struct TYPE_8__ {scalar_t__ join_rel_hash; int /*<<< orphan*/  join_rel_list; } ;
struct TYPE_7__ {int /*<<< orphan*/  relids; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ PlannerInfo ;
typedef  TYPE_3__ JoinHashEntry ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 scalar_t__ hash_search (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
add_join_rel(PlannerInfo *root, RelOptInfo *joinrel)
{
	/* GEQO requires us to append the new joinrel to the end of the list! */
	root->join_rel_list = lappend(root->join_rel_list, joinrel);

	/* store it into the auxiliary hashtable if there is one. */
	if (root->join_rel_hash)
	{
		JoinHashEntry *hentry;
		bool		found;

		hentry = (JoinHashEntry *) hash_search(root->join_rel_hash,
											   &(joinrel->relids),
											   HASH_ENTER,
											   &found);
		Assert(!found);
		hentry->join_rel = joinrel;
	}
}