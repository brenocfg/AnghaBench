#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int header; scalar_t__ children; } ;
struct TYPE_9__ {int nElems; char* dataProper; int /*<<< orphan*/  state; scalar_t__ children; int /*<<< orphan*/  isScalar; struct TYPE_9__* parent; TYPE_2__* container; } ;
typedef  TYPE_1__ JsonbIterator ;
typedef  TYPE_2__ JsonbContainer ;
typedef  int /*<<< orphan*/  JEntry ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  JBI_ARRAY_START ; 
 int /*<<< orphan*/  JBI_OBJECT_START ; 
#define  JB_FARRAY 129 
#define  JB_FOBJECT 128 
 int /*<<< orphan*/  JsonContainerIsScalar (TYPE_2__*) ; 
 int JsonContainerSize (TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* palloc0 (int) ; 

__attribute__((used)) static JsonbIterator *
iteratorFromContainer(JsonbContainer *container, JsonbIterator *parent)
{
	JsonbIterator *it;

	it = palloc0(sizeof(JsonbIterator));
	it->container = container;
	it->parent = parent;
	it->nElems = JsonContainerSize(container);

	/* Array starts just after header */
	it->children = container->children;

	switch (container->header & (JB_FARRAY | JB_FOBJECT))
	{
		case JB_FARRAY:
			it->dataProper =
				(char *) it->children + it->nElems * sizeof(JEntry);
			it->isScalar = JsonContainerIsScalar(container);
			/* This is either a "raw scalar", or an array */
			Assert(!it->isScalar || it->nElems == 1);

			it->state = JBI_ARRAY_START;
			break;

		case JB_FOBJECT:
			it->dataProper =
				(char *) it->children + it->nElems * sizeof(JEntry) * 2;
			it->state = JBI_OBJECT_START;
			break;

		default:
			elog(ERROR, "unknown type of jsonb container");
	}

	return it;
}