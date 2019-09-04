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
 int test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int tag_get(const struct radix_tree_node *node, unsigned int tag,
		int offset)
{
	return test_bit(offset, node->tags[tag]);
}