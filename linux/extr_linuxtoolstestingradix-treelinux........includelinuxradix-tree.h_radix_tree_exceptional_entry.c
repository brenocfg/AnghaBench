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
 unsigned long RADIX_TREE_EXCEPTIONAL_ENTRY ; 

__attribute__((used)) static inline int radix_tree_exceptional_entry(void *arg)
{
	/* Not unlikely because radix_tree_exception often tested first */
	return (unsigned long)arg & RADIX_TREE_EXCEPTIONAL_ENTRY;
}