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
struct node {struct node* parent; struct node* right; struct node* left; } ;

/* Variables and functions */

__attribute__((used)) static struct node *node_next(struct sparsebit *s, struct node *np)
{
	struct node *nodep = np;

	/*
	 * If current node has a right child, next node is the left-most
	 * of the right child.
	 */
	if (nodep->right) {
		for (nodep = nodep->right; nodep->left; nodep = nodep->left)
			;
		return nodep;
	}

	/*
	 * No right child.  Go up until node is left child of a parent.
	 * That parent is then the next node.
	 */
	while (nodep->parent && nodep == nodep->parent->right)
		nodep = nodep->parent;

	return nodep->parent;
}