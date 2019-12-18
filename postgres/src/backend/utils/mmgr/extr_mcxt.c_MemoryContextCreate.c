#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int isReset; char const* name; int allowInCritSection; struct TYPE_5__* nextchild; struct TYPE_5__* firstchild; struct TYPE_5__* prevchild; int /*<<< orphan*/ * reset_cbs; int /*<<< orphan*/ * ident; scalar_t__ mem_allocated; struct TYPE_5__* parent; int /*<<< orphan*/  const* methods; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  NodeTag ;
typedef  int /*<<< orphan*/  MemoryContextMethods ;
typedef  TYPE_1__* MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CritSectionCount ; 
 int /*<<< orphan*/  VALGRIND_CREATE_MEMPOOL (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
MemoryContextCreate(MemoryContext node,
					NodeTag tag,
					const MemoryContextMethods *methods,
					MemoryContext parent,
					const char *name)
{
	/* Creating new memory contexts is not allowed in a critical section */
	Assert(CritSectionCount == 0);

	/* Initialize all standard fields of memory context header */
	node->type = tag;
	node->isReset = true;
	node->methods = methods;
	node->parent = parent;
	node->firstchild = NULL;
	node->mem_allocated = 0;
	node->prevchild = NULL;
	node->name = name;
	node->ident = NULL;
	node->reset_cbs = NULL;

	/* OK to link node into context tree */
	if (parent)
	{
		node->nextchild = parent->firstchild;
		if (parent->firstchild != NULL)
			parent->firstchild->prevchild = node;
		parent->firstchild = node;
		/* inherit allowInCritSection flag from parent */
		node->allowInCritSection = parent->allowInCritSection;
	}
	else
	{
		node->nextchild = NULL;
		node->allowInCritSection = false;
	}

	VALGRIND_CREATE_MEMPOOL(node, 0, false);
}