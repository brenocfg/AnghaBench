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
struct tree {char* type; int maxage; scalar_t__ childnode; int /*<<< orphan*/  (* leaf_equal ) (void*,void*) ;struct node* root; } ;
struct node {scalar_t__ leftnode; scalar_t__ rightnode; int keymask; int bitnum; struct node* parent; struct node* right; struct node* left; int /*<<< orphan*/  keybits; scalar_t__ nextbyte; } ;

/* Variables and functions */
 scalar_t__ LEAF ; 
 scalar_t__ NODE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (struct node*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stub1 (void*,void*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void prune(struct tree *tree)
{
	struct node *node;
	struct node *left;
	struct node *right;
	struct node *parent;
	void *leftleaf;
	void *rightleaf;
	unsigned int leftmask;
	unsigned int rightmask;
	unsigned int bitmask;
	int count;

	if (verbose > 0)
		printf("Pruning %s_%x\n", tree->type, tree->maxage);

	count = 0;
	if (tree->childnode == LEAF)
		return;
	if (!tree->root)
		return;

	leftmask = rightmask = 0;
	node = tree->root;
	while (node) {
		if (node->nextbyte)
			goto advance;
		if (node->leftnode == LEAF)
			goto advance;
		if (node->rightnode == LEAF)
			goto advance;
		if (!node->left)
			goto advance;
		if (!node->right)
			goto advance;
		left = node->left;
		right = node->right;
		if (left->keymask == 0)
			goto advance;
		if (right->keymask == 0)
			goto advance;
		if (left->keymask != right->keymask)
			goto advance;
		if (left->keybits != right->keybits)
			goto advance;
		leftleaf = NULL;
		while (!leftleaf) {
			assert(left->left || left->right);
			if (left->leftnode == LEAF)
				leftleaf = left->left;
			else if (left->rightnode == LEAF)
				leftleaf = left->right;
			else if (left->left)
				left = left->left;
			else if (left->right)
				left = left->right;
			else
				assert(0);
		}
		rightleaf = NULL;
		while (!rightleaf) {
			assert(right->left || right->right);
			if (right->leftnode == LEAF)
				rightleaf = right->left;
			else if (right->rightnode == LEAF)
				rightleaf = right->right;
			else if (right->left)
				right = right->left;
			else if (right->right)
				right = right->right;
			else
				assert(0);
		}
		if (! tree->leaf_equal(leftleaf, rightleaf))
			goto advance;
		/*
		 * This node has identical singleton-only subtrees.
		 * Remove it.
		 */
		parent = node->parent;
		left = node->left;
		right = node->right;
		if (parent->left == node)
			parent->left = left;
		else if (parent->right == node)
			parent->right = left;
		else
			assert(0);
		left->parent = parent;
		left->keymask |= (1 << node->bitnum);
		node->left = NULL;
		while (node) {
			bitmask = 1 << node->bitnum;
			leftmask &= ~bitmask;
			rightmask &= ~bitmask;
			if (node->leftnode == NODE && node->left) {
				left = node->left;
				free(node);
				count++;
				node = left;
			} else if (node->rightnode == NODE && node->right) {
				right = node->right;
				free(node);
				count++;
				node = right;
			} else {
				node = NULL;
			}
		}
		/* Propagate keymasks up along singleton chains. */
		node = parent;
		/* Force re-check */
		bitmask = 1 << node->bitnum;
		leftmask &= ~bitmask;
		rightmask &= ~bitmask;
		for (;;) {
			if (node->left && node->right)
				break;
			if (node->left) {
				left = node->left;
				node->keymask |= left->keymask;
				node->keybits |= left->keybits;
			}
			if (node->right) {
				right = node->right;
				node->keymask |= right->keymask;
				node->keybits |= right->keybits;
			}
			node->keymask |= (1 << node->bitnum);
			node = node->parent;
			/* Force re-check */
			bitmask = 1 << node->bitnum;
			leftmask &= ~bitmask;
			rightmask &= ~bitmask;
		}
	advance:
		bitmask = 1 << node->bitnum;
		if ((leftmask & bitmask) == 0 &&
		    node->leftnode == NODE &&
		    node->left) {
			leftmask |= bitmask;
			node = node->left;
		} else if ((rightmask & bitmask) == 0 &&
			   node->rightnode == NODE &&
			   node->right) {
			rightmask |= bitmask;
			node = node->right;
		} else {
			leftmask &= ~bitmask;
			rightmask &= ~bitmask;
			node = node->parent;
		}
	}
	if (verbose > 0)
		printf("Pruned %d nodes\n", count);
}