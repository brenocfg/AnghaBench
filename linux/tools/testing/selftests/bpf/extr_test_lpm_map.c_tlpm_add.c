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
struct tlpm_node {size_t n_bits; int /*<<< orphan*/  key; struct tlpm_node* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct tlpm_node*) ; 
 struct tlpm_node* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 struct tlpm_node* tlpm_match (struct tlpm_node*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static struct tlpm_node *tlpm_add(struct tlpm_node *list,
				  const uint8_t *key,
				  size_t n_bits)
{
	struct tlpm_node *node;
	size_t n;

	n = (n_bits + 7) / 8;

	/* 'overwrite' an equivalent entry if one already exists */
	node = tlpm_match(list, key, n_bits);
	if (node && node->n_bits == n_bits) {
		memcpy(node->key, key, n);
		return list;
	}

	/* add new entry with @key/@n_bits to @list and return new head */

	node = malloc(sizeof(*node) + n);
	assert(node);

	node->next = list;
	node->n_bits = n_bits;
	memcpy(node->key, key, n);

	return node;
}