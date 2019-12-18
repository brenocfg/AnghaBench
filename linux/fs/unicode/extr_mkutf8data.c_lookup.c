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
struct tree {struct node* root; } ;
struct node {int bitnum; scalar_t__ rightnode; scalar_t__ leftnode; struct node* left; struct node* right; scalar_t__ nextbyte; } ;

/* Variables and functions */
 scalar_t__ LEAF ; 
 scalar_t__ NODE ; 

__attribute__((used)) static void *lookup(struct tree *tree, const char *key)
{
	struct node *node;
	void *leaf = NULL;

	node = tree->root;
	while (!leaf && node) {
		if (node->nextbyte)
			key++;
		if (*key & (1 << (node->bitnum & 7))) {
			/* Right leg */
			if (node->rightnode == NODE) {
				node = node->right;
			} else if (node->rightnode == LEAF) {
				leaf = node->right;
			} else {
				node = NULL;
			}
		} else {
			/* Left leg */
			if (node->leftnode == NODE) {
				node = node->left;
			} else if (node->leftnode == LEAF) {
				leaf = node->left;
			} else {
				node = NULL;
			}
		}
	}

	return leaf;
}