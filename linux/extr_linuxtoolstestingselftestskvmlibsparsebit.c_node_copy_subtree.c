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
struct node {struct node* parent; struct node* right; struct node* left; int /*<<< orphan*/  num_after; int /*<<< orphan*/  mask; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 struct node* calloc (int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static struct node *node_copy_subtree(struct node *subtree)
{
	struct node *root;

	/* Duplicate the node at the root of the subtree */
	root = calloc(1, sizeof(*root));
	if (!root) {
		perror("calloc");
		abort();
	}

	root->idx = subtree->idx;
	root->mask = subtree->mask;
	root->num_after = subtree->num_after;

	/* As needed, recursively duplicate the left and right subtrees */
	if (subtree->left) {
		root->left = node_copy_subtree(subtree->left);
		root->left->parent = root;
	}

	if (subtree->right) {
		root->right = node_copy_subtree(subtree->right);
		root->right->parent = root;
	}

	return root;
}