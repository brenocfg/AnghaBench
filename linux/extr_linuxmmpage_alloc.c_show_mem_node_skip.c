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
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 unsigned int SHOW_MEM_FILTER_NODES ; 
 int /*<<< orphan*/  cpuset_current_mems_allowed ; 
 int /*<<< orphan*/  node_isset (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool show_mem_node_skip(unsigned int flags, int nid, nodemask_t *nodemask)
{
	if (!(flags & SHOW_MEM_FILTER_NODES))
		return false;

	/*
	 * no node mask - aka implicit memory numa policy. Do not bother with
	 * the synchronization - read_mems_allowed_begin - because we do not
	 * have to be precise here.
	 */
	if (!nodemask)
		nodemask = &cpuset_current_mems_allowed;

	return !node_isset(nid, *nodemask);
}