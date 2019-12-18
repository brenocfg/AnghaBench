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
 int MAX_NUMNODES ; 
 int __first_node (int /*<<< orphan*/  const*) ; 
 int __next_node (int,int /*<<< orphan*/  const*) ; 

int __next_node_in(int node, const nodemask_t *srcp)
{
	int ret = __next_node(node, srcp);

	if (ret == MAX_NUMNODES)
		ret = __first_node(srcp);
	return ret;
}