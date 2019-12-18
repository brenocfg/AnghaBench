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
struct item {unsigned long order; unsigned long index; } ;

/* Variables and functions */
 unsigned long BITS_PER_LONG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  radix_tree_is_internal_node (struct item*) ; 

void item_sanity(struct item *item, unsigned long index)
{
	unsigned long mask;
	assert(!radix_tree_is_internal_node(item));
	assert(item->order < BITS_PER_LONG);
	mask = (1UL << item->order) - 1;
	assert((item->index | mask) == (index | mask));
}