#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* name; char* sort_value; int /*<<< orphan*/  rank; } ;
typedef  TYPE_1__ pivot_field ;
struct TYPE_7__ {int /*<<< orphan*/  root; int /*<<< orphan*/  count; } ;
typedef  TYPE_2__ avl_tree ;

/* Variables and functions */
 int /*<<< orphan*/  avlInsertNode (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__) ; 

__attribute__((used)) static void
avlMergeValue(avl_tree *tree, char *name, char *sort_value)
{
	pivot_field field;

	field.name = name;
	field.rank = tree->count;
	field.sort_value = sort_value;
	avlInsertNode(tree, &tree->root, field);
}