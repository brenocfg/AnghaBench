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
struct sparsebit {scalar_t__ num_set; struct node* root; } ;
struct node {struct node* right; struct node* left; struct node* parent; } ;
typedef  scalar_t__ sparsebit_num_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (struct node*) ; 
 scalar_t__ node_num_set (struct node*) ; 
 scalar_t__ sparsebit_all_set (struct sparsebit*) ; 

__attribute__((used)) static void node_rm(struct sparsebit *s, struct node *nodep)
{
	struct node *tmp;
	sparsebit_num_t num_set;

	num_set = node_num_set(nodep);
	assert(s->num_set >= num_set || sparsebit_all_set(s));
	s->num_set -= node_num_set(nodep);

	/* Have both left and right child */
	if (nodep->left && nodep->right) {
		/*
		 * Move left children to the leftmost leaf node
		 * of the right child.
		 */
		for (tmp = nodep->right; tmp->left; tmp = tmp->left)
			;
		tmp->left = nodep->left;
		nodep->left = NULL;
		tmp->left->parent = tmp;
	}

	/* Left only child */
	if (nodep->left) {
		if (!nodep->parent) {
			s->root = nodep->left;
			nodep->left->parent = NULL;
		} else {
			nodep->left->parent = nodep->parent;
			if (nodep == nodep->parent->left)
				nodep->parent->left = nodep->left;
			else {
				assert(nodep == nodep->parent->right);
				nodep->parent->right = nodep->left;
			}
		}

		nodep->parent = nodep->left = nodep->right = NULL;
		free(nodep);

		return;
	}


	/* Right only child */
	if (nodep->right) {
		if (!nodep->parent) {
			s->root = nodep->right;
			nodep->right->parent = NULL;
		} else {
			nodep->right->parent = nodep->parent;
			if (nodep == nodep->parent->left)
				nodep->parent->left = nodep->right;
			else {
				assert(nodep == nodep->parent->right);
				nodep->parent->right = nodep->right;
			}
		}

		nodep->parent = nodep->left = nodep->right = NULL;
		free(nodep);

		return;
	}

	/* Leaf Node */
	if (!nodep->parent) {
		s->root = NULL;
	} else {
		if (nodep->parent->left == nodep)
			nodep->parent->left = NULL;
		else {
			assert(nodep == nodep->parent->right);
			nodep->parent->right = NULL;
		}
	}

	nodep->parent = nodep->left = nodep->right = NULL;
	free(nodep);

	return;
}