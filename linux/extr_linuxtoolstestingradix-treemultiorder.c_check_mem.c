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
struct radix_tree_preload {scalar_t__ nr; } ;

/* Variables and functions */
 unsigned int nr_allocated ; 
 int /*<<< orphan*/  printv (int,char*,unsigned int,unsigned int,unsigned int,...) ; 
 struct radix_tree_preload radix_tree_preloads ; 

__attribute__((used)) static void check_mem(unsigned old_order, unsigned new_order, unsigned alloc)
{
	struct radix_tree_preload *rtp = &radix_tree_preloads;
	if (rtp->nr != 0)
		printv(2, "split(%u %u) remaining %u\n", old_order, new_order,
							rtp->nr);
	/*
	 * Can't check for equality here as some nodes may have been
	 * RCU-freed while we ran.  But we should never finish with more
	 * nodes allocated since they should have all been preloaded.
	 */
	if (nr_allocated > alloc)
		printv(2, "split(%u %u) allocated %u %u\n", old_order, new_order,
							alloc, nr_allocated);
}