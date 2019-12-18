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
struct sparsebit {int dummy; } ;
struct node {struct node* parent; struct node* left; struct node* right; } ;

/* Variables and functions */

__attribute__((used)) static struct node *node_prev(struct sparsebit *s, struct node *np)
{
	struct node *nodep = np;

	/*
	 * If current node has a left child, next node is the right-most
	 * of the left child.
	 */
	if (nodep->left) {
		for (nodep = nodep->left; nodep->right; nodep = nodep->right)
			;
		return (struct node *) nodep;
	}

	/*
	 * No left child.  Go up until node is right child of a parent.
	 * That parent is then the next node.
	 */
	while (nodep->parent && nodep == nodep->parent->left)
		nodep = nodep->parent;

	return (struct node *) nodep->parent;
}