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
struct sparsebit {struct node* root; } ;
struct node {int idx; int num_after; struct node* right; struct node* left; } ;
typedef  int sparsebit_idx_t ;

/* Variables and functions */
 int MASK_BITS ; 

__attribute__((used)) static struct node *node_find(struct sparsebit *s, sparsebit_idx_t idx)
{
	struct node *nodep;

	/* Find the node that describes the setting of the bit at idx */
	for (nodep = s->root; nodep;
	     nodep = nodep->idx > idx ? nodep->left : nodep->right) {
		if (idx >= nodep->idx &&
		    idx <= nodep->idx + MASK_BITS + nodep->num_after - 1)
			break;
	}

	return nodep;
}