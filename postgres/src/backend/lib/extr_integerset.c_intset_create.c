#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int iter_active; int /*<<< orphan*/ * iter_values; scalar_t__ iter_num_values; scalar_t__ iter_valueno; scalar_t__ iter_itemno; int /*<<< orphan*/ * iter_node; scalar_t__ num_buffered_values; int /*<<< orphan*/ * leftmost_leaf; int /*<<< orphan*/  rightmost_nodes; int /*<<< orphan*/ * root; scalar_t__ num_levels; scalar_t__ highest_value; scalar_t__ num_entries; int /*<<< orphan*/  mem_used; int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ IntegerSet ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  GetMemoryChunkSpace (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc (int) ; 

IntegerSet *
intset_create(void)
{
	IntegerSet *intset;

	intset = (IntegerSet *) palloc(sizeof(IntegerSet));
	intset->context = CurrentMemoryContext;
	intset->mem_used = GetMemoryChunkSpace(intset);

	intset->num_entries = 0;
	intset->highest_value = 0;

	intset->num_levels = 0;
	intset->root = NULL;
	memset(intset->rightmost_nodes, 0, sizeof(intset->rightmost_nodes));
	intset->leftmost_leaf = NULL;

	intset->num_buffered_values = 0;

	intset->iter_active = false;
	intset->iter_node = NULL;
	intset->iter_itemno = 0;
	intset->iter_valueno = 0;
	intset->iter_num_values = 0;
	intset->iter_values = NULL;

	return intset;
}