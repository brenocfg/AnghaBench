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
struct sidtab_node {struct sidtab_node* next; } ;
struct sidtab {int /*<<< orphan*/  nel; struct sidtab_node** htable; } ;

/* Variables and functions */
 int SIDTAB_SIZE ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int /*<<< orphan*/ ,int,int,int) ; 

void sidtab_hash_eval(struct sidtab *h, char *tag)
{
	int i, chain_len, slots_used, max_chain_len;
	struct sidtab_node *cur;

	slots_used = 0;
	max_chain_len = 0;
	for (i = 0; i < SIDTAB_SIZE; i++) {
		cur = h->htable[i];
		if (cur) {
			slots_used++;
			chain_len = 0;
			while (cur) {
				chain_len++;
				cur = cur->next;
			}

			if (chain_len > max_chain_len)
				max_chain_len = chain_len;
		}
	}

	pr_debug("%s:  %d entries and %d/%d buckets used, longest "
	       "chain length %d\n", tag, h->nel, slots_used, SIDTAB_SIZE,
	       max_chain_len);
}