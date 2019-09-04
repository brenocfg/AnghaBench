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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_KERNEL ; 
 void* __vmalloc_node (unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 

void *__vmalloc_node_flags_caller(unsigned long size, int node, gfp_t flags,
				  void *caller)
{
	return __vmalloc_node(size, 1, flags, PAGE_KERNEL, node, caller);
}