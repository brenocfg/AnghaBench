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
 int /*<<< orphan*/  assert (int) ; 
 int radix_tree_gang_lookup (struct radix_tree_root*,void**,unsigned long,int) ; 

void item_gang_check_present(struct radix_tree_root *root,
			unsigned long start, unsigned long nr,
			int chunk, int hop)
{
	struct item *items[chunk];
	unsigned long into;

	for (into = 0; into < nr; ) {
		int nfound;
		int nr_to_find = chunk;
		int i;

		if (nr_to_find > (nr - into))
			nr_to_find = nr - into;

		nfound = radix_tree_gang_lookup(root, (void **)items,
						start + into, nr_to_find);
		assert(nfound == nr_to_find);
		for (i = 0; i < nfound; i++)
			assert(items[i]->index == start + into + i);
		into += hop;
	}
}