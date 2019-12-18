#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {void* pairs; int /*<<< orphan*/  nPairs; } ;
struct TYPE_19__ {int rawScalar; int nElems; void* elems; } ;
struct TYPE_21__ {TYPE_2__ object; TYPE_1__ array; } ;
struct TYPE_22__ {int type; TYPE_3__ val; } ;
struct TYPE_23__ {int size; TYPE_4__ contVal; struct TYPE_23__* next; } ;
typedef  TYPE_4__ JsonbValue ;
typedef  TYPE_5__ JsonbParseState ;
typedef  int /*<<< orphan*/  JsonbPair ;
typedef  int JsonbIteratorToken ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int IsAJsonbScalar (TYPE_4__*) ; 
#define  WJB_BEGIN_ARRAY 136 
#define  WJB_BEGIN_OBJECT 135 
#define  WJB_ELEM 134 
#define  WJB_END_ARRAY 133 
#define  WJB_END_OBJECT 132 
#define  WJB_KEY 131 
#define  WJB_VALUE 130 
 int /*<<< orphan*/  appendElement (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  appendKey (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  appendValue (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
#define  jbvArray 129 
#define  jbvObject 128 
 int jbvString ; 
 void* palloc (int) ; 
 TYPE_5__* pushState (TYPE_5__**) ; 
 int /*<<< orphan*/  uniqueifyJsonbObject (TYPE_4__*) ; 

__attribute__((used)) static JsonbValue *
pushJsonbValueScalar(JsonbParseState **pstate, JsonbIteratorToken seq,
					 JsonbValue *scalarVal)
{
	JsonbValue *result = NULL;

	switch (seq)
	{
		case WJB_BEGIN_ARRAY:
			Assert(!scalarVal || scalarVal->val.array.rawScalar);
			*pstate = pushState(pstate);
			result = &(*pstate)->contVal;
			(*pstate)->contVal.type = jbvArray;
			(*pstate)->contVal.val.array.nElems = 0;
			(*pstate)->contVal.val.array.rawScalar = (scalarVal &&
													  scalarVal->val.array.rawScalar);
			if (scalarVal && scalarVal->val.array.nElems > 0)
			{
				/* Assume that this array is still really a scalar */
				Assert(scalarVal->type == jbvArray);
				(*pstate)->size = scalarVal->val.array.nElems;
			}
			else
			{
				(*pstate)->size = 4;
			}
			(*pstate)->contVal.val.array.elems = palloc(sizeof(JsonbValue) *
														(*pstate)->size);
			break;
		case WJB_BEGIN_OBJECT:
			Assert(!scalarVal);
			*pstate = pushState(pstate);
			result = &(*pstate)->contVal;
			(*pstate)->contVal.type = jbvObject;
			(*pstate)->contVal.val.object.nPairs = 0;
			(*pstate)->size = 4;
			(*pstate)->contVal.val.object.pairs = palloc(sizeof(JsonbPair) *
														 (*pstate)->size);
			break;
		case WJB_KEY:
			Assert(scalarVal->type == jbvString);
			appendKey(*pstate, scalarVal);
			break;
		case WJB_VALUE:
			Assert(IsAJsonbScalar(scalarVal));
			appendValue(*pstate, scalarVal);
			break;
		case WJB_ELEM:
			Assert(IsAJsonbScalar(scalarVal));
			appendElement(*pstate, scalarVal);
			break;
		case WJB_END_OBJECT:
			uniqueifyJsonbObject(&(*pstate)->contVal);
			/* fall through! */
		case WJB_END_ARRAY:
			/* Steps here common to WJB_END_OBJECT case */
			Assert(!scalarVal);
			result = &(*pstate)->contVal;

			/*
			 * Pop stack and push current array/object as value in parent
			 * array/object
			 */
			*pstate = (*pstate)->next;
			if (*pstate)
			{
				switch ((*pstate)->contVal.type)
				{
					case jbvArray:
						appendElement(*pstate, result);
						break;
					case jbvObject:
						appendValue(*pstate, result);
						break;
					default:
						elog(ERROR, "invalid jsonb container type");
				}
			}
			break;
		default:
			elog(ERROR, "unrecognized jsonb sequential processing token");
	}

	return result;
}