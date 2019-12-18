#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {struct TYPE_16__* parent; } ;
struct TYPE_13__ {int /*<<< orphan*/  nPairs; } ;
struct TYPE_12__ {int /*<<< orphan*/  nElems; int /*<<< orphan*/  rawScalar; } ;
struct TYPE_14__ {TYPE_2__ object; TYPE_1__ array; } ;
struct TYPE_15__ {int type; TYPE_3__ val; } ;
typedef  TYPE_4__ JsonbValue ;
typedef  scalar_t__ JsonbIteratorToken ;
typedef  TYPE_5__ JsonbIterator ;
typedef  int /*<<< orphan*/  JsonbContainer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_5__* JsonbIteratorInit (int /*<<< orphan*/ *) ; 
 scalar_t__ JsonbIteratorNext (TYPE_5__**,TYPE_4__*,int) ; 
 scalar_t__ WJB_DONE ; 
 scalar_t__ WJB_END_ARRAY ; 
 scalar_t__ WJB_END_OBJECT ; 
 int compareJsonbScalarValue (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
#define  jbvArray 135 
#define  jbvBinary 134 
#define  jbvBool 133 
#define  jbvDatetime 132 
#define  jbvNull 131 
#define  jbvNumeric 130 
#define  jbvObject 129 
#define  jbvString 128 
 int /*<<< orphan*/  pfree (TYPE_5__*) ; 

int
compareJsonbContainers(JsonbContainer *a, JsonbContainer *b)
{
	JsonbIterator *ita,
			   *itb;
	int			res = 0;

	ita = JsonbIteratorInit(a);
	itb = JsonbIteratorInit(b);

	do
	{
		JsonbValue	va,
					vb;
		JsonbIteratorToken ra,
					rb;

		ra = JsonbIteratorNext(&ita, &va, false);
		rb = JsonbIteratorNext(&itb, &vb, false);

		if (ra == rb)
		{
			if (ra == WJB_DONE)
			{
				/* Decisively equal */
				break;
			}

			if (ra == WJB_END_ARRAY || ra == WJB_END_OBJECT)
			{
				/*
				 * There is no array or object to compare at this stage of
				 * processing.  jbvArray/jbvObject values are compared
				 * initially, at the WJB_BEGIN_ARRAY and WJB_BEGIN_OBJECT
				 * tokens.
				 */
				continue;
			}

			if (va.type == vb.type)
			{
				switch (va.type)
				{
					case jbvString:
					case jbvNull:
					case jbvNumeric:
					case jbvBool:
						res = compareJsonbScalarValue(&va, &vb);
						break;
					case jbvArray:

						/*
						 * This could be a "raw scalar" pseudo array.  That's
						 * a special case here though, since we still want the
						 * general type-based comparisons to apply, and as far
						 * as we're concerned a pseudo array is just a scalar.
						 */
						if (va.val.array.rawScalar != vb.val.array.rawScalar)
							res = (va.val.array.rawScalar) ? -1 : 1;
						if (va.val.array.nElems != vb.val.array.nElems)
							res = (va.val.array.nElems > vb.val.array.nElems) ? 1 : -1;
						break;
					case jbvObject:
						if (va.val.object.nPairs != vb.val.object.nPairs)
							res = (va.val.object.nPairs > vb.val.object.nPairs) ? 1 : -1;
						break;
					case jbvBinary:
						elog(ERROR, "unexpected jbvBinary value");
						break;
					case jbvDatetime:
						elog(ERROR, "unexpected jbvDatetime value");
						break;
				}
			}
			else
			{
				/* Type-defined order */
				res = (va.type > vb.type) ? 1 : -1;
			}
		}
		else
		{
			/*
			 * It's safe to assume that the types differed, and that the va
			 * and vb values passed were set.
			 *
			 * If the two values were of the same container type, then there'd
			 * have been a chance to observe the variation in the number of
			 * elements/pairs (when processing WJB_BEGIN_OBJECT, say). They're
			 * either two heterogeneously-typed containers, or a container and
			 * some scalar type.
			 *
			 * We don't have to consider the WJB_END_ARRAY and WJB_END_OBJECT
			 * cases here, because we would have seen the corresponding
			 * WJB_BEGIN_ARRAY and WJB_BEGIN_OBJECT tokens first, and
			 * concluded that they don't match.
			 */
			Assert(ra != WJB_END_ARRAY && ra != WJB_END_OBJECT);
			Assert(rb != WJB_END_ARRAY && rb != WJB_END_OBJECT);

			Assert(va.type != vb.type);
			Assert(va.type != jbvBinary);
			Assert(vb.type != jbvBinary);
			/* Type-defined order */
			res = (va.type > vb.type) ? 1 : -1;
		}
	}
	while (res == 0);

	while (ita != NULL)
	{
		JsonbIterator *i = ita->parent;

		pfree(ita);
		ita = i;
	}
	while (itb != NULL)
	{
		JsonbIterator *i = itb->parent;

		pfree(itb);
		itb = i;
	}

	return res;
}