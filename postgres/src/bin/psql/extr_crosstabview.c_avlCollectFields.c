#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pivot_field ;
struct TYPE_5__ {TYPE_2__* end; } ;
typedef  TYPE_1__ avl_tree ;
struct TYPE_6__ {struct TYPE_6__** children; int /*<<< orphan*/  field; } ;
typedef  TYPE_2__ avl_node ;

/* Variables and functions */

__attribute__((used)) static int
avlCollectFields(avl_tree *tree, avl_node *node, pivot_field *fields, int idx)
{
	if (node == tree->end)
		return idx;

	idx = avlCollectFields(tree, node->children[0], fields, idx);
	fields[idx] = node->field;
	return avlCollectFields(tree, node->children[1], fields, idx + 1);
}