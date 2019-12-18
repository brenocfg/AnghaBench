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
struct TYPE_6__ {int /*<<< orphan*/ * next; scalar_t__ num_items; scalar_t__ level; } ;
typedef  TYPE_1__ intset_leaf_node ;
struct TYPE_7__ {int /*<<< orphan*/  mem_used; int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ IntegerSet ;

/* Variables and functions */
 scalar_t__ GetMemoryChunkSpace (TYPE_1__*) ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static intset_leaf_node *
intset_new_leaf_node(IntegerSet *intset)
{
	intset_leaf_node *n;

	n = (intset_leaf_node *) MemoryContextAlloc(intset->context,
												sizeof(intset_leaf_node));
	intset->mem_used += GetMemoryChunkSpace(n);

	n->level = 0;
	n->num_items = 0;
	n->next = NULL;

	return n;
}