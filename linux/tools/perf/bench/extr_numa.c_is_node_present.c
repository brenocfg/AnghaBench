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
 int numa_bitmask_isbitset (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  numa_nodes_ptr ; 

__attribute__((used)) static int is_node_present(int node)
{
	return numa_bitmask_isbitset(numa_nodes_ptr, node);
}