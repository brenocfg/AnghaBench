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
struct radix_tree_iter {unsigned int index; } ;

/* Variables and functions */
 unsigned int RADIX_TREE_MAP_MASK ; 

__attribute__((used)) static unsigned int iter_offset(const struct radix_tree_iter *iter)
{
	return iter->index & RADIX_TREE_MAP_MASK;
}