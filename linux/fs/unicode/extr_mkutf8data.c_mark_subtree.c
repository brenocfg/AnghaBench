#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct node {int mark; scalar_t__ leftnode; scalar_t__ rightnode; struct node* right; struct node* left; TYPE_1__* parent; int /*<<< orphan*/  index; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 scalar_t__ NODE ; 

__attribute__((used)) static int mark_subtree(struct node *node)
{
	int changed;

	if (!node || node->mark)
		return 0;
	node->mark = 1;
	node->index = node->parent->index;
	changed = 1;
	if (node->leftnode == NODE)
		changed += mark_subtree(node->left);
	if (node->rightnode == NODE)
		changed += mark_subtree(node->right);
	return changed;
}