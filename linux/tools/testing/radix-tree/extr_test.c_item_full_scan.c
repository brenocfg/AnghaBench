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

void item_full_scan(struct radix_tree_root *root, unsigned long start,
			unsigned long nr, int chunk)
{
	struct item *items[chunk];
	unsigned long into = 0;
	unsigned long this_index = start;
	int nfound;
	int i;

//	printf("%s(0x%08lx, 0x%08lx, %d)\n", __FUNCTION__, start, nr, chunk);

	while ((nfound = radix_tree_gang_lookup(root, (void **)items, into,
					chunk))) {
//		printf("At 0x%08lx, nfound=%d\n", into, nfound);
		for (i = 0; i < nfound; i++) {
			assert(items[i]->index == this_index);
			this_index++;
		}
//		printf("Found 0x%08lx->0x%08lx\n",
//			items[0]->index, items[nfound-1]->index);
		into = this_index;
	}
	if (chunk)
		assert(this_index == start + nr);
	nfound = radix_tree_gang_lookup(root, (void **)items,
					this_index, chunk);
	assert(nfound == 0);
}