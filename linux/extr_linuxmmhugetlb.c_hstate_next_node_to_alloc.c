#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hstate {int /*<<< orphan*/  next_nid_to_alloc; } ;
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int get_valid_node_allowed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_node_allowed (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hstate_next_node_to_alloc(struct hstate *h,
					nodemask_t *nodes_allowed)
{
	int nid;

	VM_BUG_ON(!nodes_allowed);

	nid = get_valid_node_allowed(h->next_nid_to_alloc, nodes_allowed);
	h->next_nid_to_alloc = next_node_allowed(nid, nodes_allowed);

	return nid;
}