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
typedef  int /*<<< orphan*/  uint8_t ;
struct tlpm_node {size_t n_bits; struct tlpm_node* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct tlpm_node*) ; 
 struct tlpm_node* tlpm_match (struct tlpm_node*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static struct tlpm_node *tlpm_delete(struct tlpm_node *list,
				     const uint8_t *key,
				     size_t n_bits)
{
	struct tlpm_node *best = tlpm_match(list, key, n_bits);
	struct tlpm_node *node;

	if (!best || best->n_bits != n_bits)
		return list;

	if (best == list) {
		node = best->next;
		free(best);
		return node;
	}

	for (node = list; node; node = node->next) {
		if (node->next == best) {
			node->next = best->next;
			free(best);
			return list;
		}
	}
	/* should never get here */
	assert(0);
	return list;
}