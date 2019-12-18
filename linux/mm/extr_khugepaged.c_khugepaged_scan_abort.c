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

/* Variables and functions */
 int MAX_NUMNODES ; 
 scalar_t__* khugepaged_node_load ; 
 scalar_t__ node_distance (int,int) ; 
 scalar_t__ node_reclaim_distance ; 
 int /*<<< orphan*/  node_reclaim_mode ; 

__attribute__((used)) static bool khugepaged_scan_abort(int nid)
{
	int i;

	/*
	 * If node_reclaim_mode is disabled, then no extra effort is made to
	 * allocate memory locally.
	 */
	if (!node_reclaim_mode)
		return false;

	/* If there is a count for this node already, it must be acceptable */
	if (khugepaged_node_load[nid])
		return false;

	for (i = 0; i < MAX_NUMNODES; i++) {
		if (!khugepaged_node_load[i])
			continue;
		if (node_distance(nid, i) > node_reclaim_distance)
			return true;
	}
	return false;
}