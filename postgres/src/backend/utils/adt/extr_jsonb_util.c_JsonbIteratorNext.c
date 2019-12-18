#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int state; size_t nElems; size_t curIndex; int /*<<< orphan*/ * children; int /*<<< orphan*/  curValueOffset; int /*<<< orphan*/  curDataOffset; int /*<<< orphan*/  dataProper; int /*<<< orphan*/  container; int /*<<< orphan*/  isScalar; } ;
struct TYPE_17__ {int /*<<< orphan*/  data; } ;
struct TYPE_16__ {size_t nPairs; } ;
struct TYPE_15__ {size_t nElems; int /*<<< orphan*/  rawScalar; } ;
struct TYPE_18__ {TYPE_3__ binary; TYPE_2__ object; TYPE_1__ array; } ;
struct TYPE_19__ {TYPE_4__ val; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ JsonbValue ;
typedef  int JsonbIteratorToken ;
typedef  TYPE_6__ JsonbIterator ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IsAJsonbScalar (TYPE_5__*) ; 
 int /*<<< orphan*/  JBE_ADVANCE_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  JBI_ARRAY_ELEM 132 
#define  JBI_ARRAY_START 131 
#define  JBI_OBJECT_KEY 130 
#define  JBI_OBJECT_START 129 
#define  JBI_OBJECT_VALUE 128 
 int WJB_BEGIN_ARRAY ; 
 int WJB_BEGIN_OBJECT ; 
 int WJB_DONE ; 
 int WJB_ELEM ; 
 int WJB_END_ARRAY ; 
 int WJB_END_OBJECT ; 
 int WJB_KEY ; 
 int WJB_VALUE ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fillJsonbValue (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 TYPE_6__* freeAndGetParent (TYPE_6__*) ; 
 int /*<<< orphan*/  getJsonbOffset (int /*<<< orphan*/ ,size_t) ; 
 TYPE_6__* iteratorFromContainer (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  jbvArray ; 
 int /*<<< orphan*/  jbvObject ; 
 int /*<<< orphan*/  jbvString ; 

JsonbIteratorToken
JsonbIteratorNext(JsonbIterator **it, JsonbValue *val, bool skipNested)
{
	if (*it == NULL)
		return WJB_DONE;

	/*
	 * When stepping into a nested container, we jump back here to start
	 * processing the child. We will not recurse further in one call, because
	 * processing the child will always begin in JBI_ARRAY_START or
	 * JBI_OBJECT_START state.
	 */
recurse:
	switch ((*it)->state)
	{
		case JBI_ARRAY_START:
			/* Set v to array on first array call */
			val->type = jbvArray;
			val->val.array.nElems = (*it)->nElems;

			/*
			 * v->val.array.elems is not actually set, because we aren't doing
			 * a full conversion
			 */
			val->val.array.rawScalar = (*it)->isScalar;
			(*it)->curIndex = 0;
			(*it)->curDataOffset = 0;
			(*it)->curValueOffset = 0;	/* not actually used */
			/* Set state for next call */
			(*it)->state = JBI_ARRAY_ELEM;
			return WJB_BEGIN_ARRAY;

		case JBI_ARRAY_ELEM:
			if ((*it)->curIndex >= (*it)->nElems)
			{
				/*
				 * All elements within array already processed.  Report this
				 * to caller, and give it back original parent iterator (which
				 * independently tracks iteration progress at its level of
				 * nesting).
				 */
				*it = freeAndGetParent(*it);
				return WJB_END_ARRAY;
			}

			fillJsonbValue((*it)->container, (*it)->curIndex,
						   (*it)->dataProper, (*it)->curDataOffset,
						   val);

			JBE_ADVANCE_OFFSET((*it)->curDataOffset,
							   (*it)->children[(*it)->curIndex]);
			(*it)->curIndex++;

			if (!IsAJsonbScalar(val) && !skipNested)
			{
				/* Recurse into container. */
				*it = iteratorFromContainer(val->val.binary.data, *it);
				goto recurse;
			}
			else
			{
				/*
				 * Scalar item in array, or a container and caller didn't want
				 * us to recurse into it.
				 */
				return WJB_ELEM;
			}

		case JBI_OBJECT_START:
			/* Set v to object on first object call */
			val->type = jbvObject;
			val->val.object.nPairs = (*it)->nElems;

			/*
			 * v->val.object.pairs is not actually set, because we aren't
			 * doing a full conversion
			 */
			(*it)->curIndex = 0;
			(*it)->curDataOffset = 0;
			(*it)->curValueOffset = getJsonbOffset((*it)->container,
												   (*it)->nElems);
			/* Set state for next call */
			(*it)->state = JBI_OBJECT_KEY;
			return WJB_BEGIN_OBJECT;

		case JBI_OBJECT_KEY:
			if ((*it)->curIndex >= (*it)->nElems)
			{
				/*
				 * All pairs within object already processed.  Report this to
				 * caller, and give it back original containing iterator
				 * (which independently tracks iteration progress at its level
				 * of nesting).
				 */
				*it = freeAndGetParent(*it);
				return WJB_END_OBJECT;
			}
			else
			{
				/* Return key of a key/value pair.  */
				fillJsonbValue((*it)->container, (*it)->curIndex,
							   (*it)->dataProper, (*it)->curDataOffset,
							   val);
				if (val->type != jbvString)
					elog(ERROR, "unexpected jsonb type as object key");

				/* Set state for next call */
				(*it)->state = JBI_OBJECT_VALUE;
				return WJB_KEY;
			}

		case JBI_OBJECT_VALUE:
			/* Set state for next call */
			(*it)->state = JBI_OBJECT_KEY;

			fillJsonbValue((*it)->container, (*it)->curIndex + (*it)->nElems,
						   (*it)->dataProper, (*it)->curValueOffset,
						   val);

			JBE_ADVANCE_OFFSET((*it)->curDataOffset,
							   (*it)->children[(*it)->curIndex]);
			JBE_ADVANCE_OFFSET((*it)->curValueOffset,
							   (*it)->children[(*it)->curIndex + (*it)->nElems]);
			(*it)->curIndex++;

			/*
			 * Value may be a container, in which case we recurse with new,
			 * child iterator (unless the caller asked not to, by passing
			 * skipNested).
			 */
			if (!IsAJsonbScalar(val) && !skipNested)
			{
				*it = iteratorFromContainer(val->val.binary.data, *it);
				goto recurse;
			}
			else
				return WJB_VALUE;
	}

	elog(ERROR, "invalid iterator state");
	return -1;
}