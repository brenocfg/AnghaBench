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
struct tree {char* type; int maxage; scalar_t__ childnode; scalar_t__ (* leaf_mark ) (int) ;struct node* root; } ;
struct node {int bitnum; scalar_t__ leftnode; int left; int mark; scalar_t__ rightnode; int right; struct node* parent; } ;

/* Variables and functions */
 scalar_t__ LEAF ; 
 scalar_t__ NODE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ stub1 (int) ; 
 scalar_t__ stub2 (int) ; 
 scalar_t__ stub3 (int) ; 
 scalar_t__ stub4 (int) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void mark_nodes(struct tree *tree)
{
	struct node *node;
	struct node *n;
	unsigned int leftmask;
	unsigned int rightmask;
	unsigned int bitmask;
	int marked;

	marked = 0;
	if (verbose > 0)
		printf("Marking %s_%x\n", tree->type, tree->maxage);
	if (tree->childnode == LEAF)
		goto done;

	assert(tree->childnode == NODE);
	node = tree->root;
	leftmask = rightmask = 0;
	while (node) {
		bitmask = 1 << node->bitnum;
		if ((leftmask & bitmask) == 0) {
			leftmask |= bitmask;
			if (node->leftnode == LEAF) {
				assert(node->left);
				if (tree->leaf_mark(node->left)) {
					n = node;
					while (n && !n->mark) {
						marked++;
						n->mark = 1;
						n = n->parent;
					}
				}
			} else if (node->left) {
				assert(node->leftnode == NODE);
				node = node->left;
				continue;
			}
		}
		if ((rightmask & bitmask) == 0) {
			rightmask |= bitmask;
			if (node->rightnode == LEAF) {
				assert(node->right);
				if (tree->leaf_mark(node->right)) {
					n = node;
					while (n && !n->mark) {
						marked++;
						n->mark = 1;
						n = n->parent;
					}
				}
			} else if (node->right) {
				assert(node->rightnode == NODE);
				node = node->right;
				continue;
			}
		}
		leftmask &= ~bitmask;
		rightmask &= ~bitmask;
		node = node->parent;
	}

	/* second pass: left siblings and singletons */

	assert(tree->childnode == NODE);
	node = tree->root;
	leftmask = rightmask = 0;
	while (node) {
		bitmask = 1 << node->bitnum;
		if ((leftmask & bitmask) == 0) {
			leftmask |= bitmask;
			if (node->leftnode == LEAF) {
				assert(node->left);
				if (tree->leaf_mark(node->left)) {
					n = node;
					while (n && !n->mark) {
						marked++;
						n->mark = 1;
						n = n->parent;
					}
				}
			} else if (node->left) {
				assert(node->leftnode == NODE);
				node = node->left;
				if (!node->mark && node->parent->mark) {
					marked++;
					node->mark = 1;
				}
				continue;
			}
		}
		if ((rightmask & bitmask) == 0) {
			rightmask |= bitmask;
			if (node->rightnode == LEAF) {
				assert(node->right);
				if (tree->leaf_mark(node->right)) {
					n = node;
					while (n && !n->mark) {
						marked++;
						n->mark = 1;
						n = n->parent;
					}
				}
			} else if (node->right) {
				assert(node->rightnode == NODE);
				node = node->right;
				if (!node->mark && node->parent->mark &&
				    !node->parent->left) {
					marked++;
					node->mark = 1;
				}
				continue;
			}
		}
		leftmask &= ~bitmask;
		rightmask &= ~bitmask;
		node = node->parent;
	}
done:
	if (verbose > 0)
		printf("Marked %d nodes\n", marked);
}