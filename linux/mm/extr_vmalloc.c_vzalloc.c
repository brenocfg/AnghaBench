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
 int GFP_KERNEL ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int __GFP_ZERO ; 
 void* __vmalloc_node_flags (unsigned long,int /*<<< orphan*/ ,int) ; 

void *vzalloc(unsigned long size)
{
	return __vmalloc_node_flags(size, NUMA_NO_NODE,
				GFP_KERNEL | __GFP_ZERO);
}