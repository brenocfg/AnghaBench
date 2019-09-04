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
struct radix_tree_node {int** tags; int shift; struct radix_tree_node** slots; } ;

/* Variables and functions */
 int RADIX_TREE_MAP_SIZE ; 
 int RADIX_TREE_MAX_TAGS ; 
 int RADIX_TREE_TAG_LONGS ; 
 int /*<<< orphan*/  assert (int) ; 
 struct radix_tree_node* entry_to_node (struct radix_tree_node*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  test_bit (int,int*) ; 

__attribute__((used)) static int verify_node(struct radix_tree_node *slot, unsigned int tag,
			int tagged)
{
	int anyset = 0;
	int i;
	int j;

	slot = entry_to_node(slot);

	/* Verify consistency at this level */
	for (i = 0; i < RADIX_TREE_TAG_LONGS; i++) {
		if (slot->tags[tag][i]) {
			anyset = 1;
			break;
		}
	}
	if (tagged != anyset) {
		printf("tag: %u, shift %u, tagged: %d, anyset: %d\n",
			tag, slot->shift, tagged, anyset);
		for (j = 0; j < RADIX_TREE_MAX_TAGS; j++) {
			printf("tag %d: ", j);
			for (i = 0; i < RADIX_TREE_TAG_LONGS; i++)
				printf("%016lx ", slot->tags[j][i]);
			printf("\n");
		}
		return 1;
	}
	assert(tagged == anyset);

	/* Go for next level */
	if (slot->shift > 0) {
		for (i = 0; i < RADIX_TREE_MAP_SIZE; i++)
			if (slot->slots[i])
				if (verify_node(slot->slots[i], tag,
					    !!test_bit(i, slot->tags[tag]))) {
					printf("Failure at off %d\n", i);
					for (j = 0; j < RADIX_TREE_MAX_TAGS; j++) {
						printf("tag %d: ", j);
						for (i = 0; i < RADIX_TREE_TAG_LONGS; i++)
							printf("%016lx ", slot->tags[j][i]);
						printf("\n");
					}
					return 1;
				}
	}
	return 0;
}