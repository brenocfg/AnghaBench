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
struct radix_tree_node {int /*<<< orphan*/ * tags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIX_TREE_MAP_SIZE ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void all_tag_set(struct radix_tree_node *node, unsigned int tag)
{
	bitmap_fill(node->tags[tag], RADIX_TREE_MAP_SIZE);
}