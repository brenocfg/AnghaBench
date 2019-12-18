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
typedef  int uint8_t ;
struct tlpm_node {size_t n_bits; int* key; struct tlpm_node* next; } ;

/* Variables and functions */

__attribute__((used)) static struct tlpm_node *tlpm_match(struct tlpm_node *list,
				    const uint8_t *key,
				    size_t n_bits)
{
	struct tlpm_node *best = NULL;
	size_t i;

	/* Perform longest prefix-match on @key/@n_bits. That is, iterate all
	 * entries and match each prefix against @key. Remember the "best"
	 * entry we find (i.e., the longest prefix that matches) and return it
	 * to the caller when done.
	 */

	for ( ; list; list = list->next) {
		for (i = 0; i < n_bits && i < list->n_bits; ++i) {
			if ((key[i / 8] & (1 << (7 - i % 8))) !=
			    (list->key[i / 8] & (1 << (7 - i % 8))))
				break;
		}

		if (i >= list->n_bits) {
			if (!best || i > best->n_bits)
				best = list;
		}
	}

	return best;
}