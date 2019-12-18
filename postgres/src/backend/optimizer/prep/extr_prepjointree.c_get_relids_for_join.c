#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ jointree; } ;
typedef  int /*<<< orphan*/  Relids ;
typedef  TYPE_1__ Query ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * find_jointree_node_for_rel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_relids_in_jointree (int /*<<< orphan*/ *,int) ; 

Relids
get_relids_for_join(Query *query, int joinrelid)
{
	Node	   *jtnode;

	jtnode = find_jointree_node_for_rel((Node *) query->jointree,
										joinrelid);
	if (!jtnode)
		elog(ERROR, "could not find join node %d", joinrelid);
	return get_relids_in_jointree(jtnode, false);
}