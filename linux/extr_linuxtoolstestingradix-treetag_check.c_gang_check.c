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
struct radix_tree_root {int dummy; } ;
struct item {unsigned long index; } ;

/* Variables and functions */
 int BATCH ; 
 char NODE_TAGGED ; 
 int /*<<< orphan*/  assert (int) ; 
 int radix_tree_gang_lookup_tag (struct radix_tree_root*,void**,unsigned long,int,int) ; 

__attribute__((used)) static void gang_check(struct radix_tree_root *tree,
			char *thrash_state, int tag)
{
	struct item *items[BATCH];
	int nr_found;
	unsigned long index = 0;
	unsigned long last_index = 0;

	while ((nr_found = radix_tree_gang_lookup_tag(tree, (void **)items,
					index, BATCH, tag))) {
		int i;

		for (i = 0; i < nr_found; i++) {
			struct item *item = items[i];

			while (last_index < item->index) {
				assert(thrash_state[last_index] != NODE_TAGGED);
				last_index++;
			}
			assert(thrash_state[last_index] == NODE_TAGGED);
			last_index++;
		}
		index = items[nr_found - 1]->index + 1;
	}
}