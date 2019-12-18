#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct TYPE_21__ {int /*<<< orphan*/  root; } ;
struct TYPE_20__ {int isScalar; } ;
struct TYPE_17__ {int rawScalar; } ;
struct TYPE_16__ {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;
struct TYPE_18__ {TYPE_2__ array; TYPE_1__ string; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_3__ val; } ;
typedef  TYPE_4__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonbParseState ;
typedef  scalar_t__ JsonbIteratorToken ;
typedef  TYPE_5__ JsonbIterator ;
typedef  TYPE_6__ Jsonb ;
typedef  int /*<<< orphan*/ * (* JsonTransformStringValuesAction ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 TYPE_5__* JsonbIteratorInit (int /*<<< orphan*/ *) ; 
 scalar_t__ JsonbIteratorNext (TYPE_5__**,TYPE_4__*,int) ; 
 TYPE_6__* JsonbValueToJsonb (TYPE_4__*) ; 
 int /*<<< orphan*/  VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 scalar_t__ WJB_BEGIN_ARRAY ; 
 scalar_t__ WJB_DONE ; 
 scalar_t__ WJB_ELEM ; 
 scalar_t__ WJB_KEY ; 
 scalar_t__ WJB_VALUE ; 
 scalar_t__ jbvArray ; 
 scalar_t__ jbvString ; 
 TYPE_4__* pushJsonbValue (int /*<<< orphan*/ **,scalar_t__,TYPE_4__*) ; 

Jsonb *
transform_jsonb_string_values(Jsonb *jsonb, void *action_state,
							  JsonTransformStringValuesAction transform_action)
{
	JsonbIterator *it;
	JsonbValue	v,
			   *res = NULL;
	JsonbIteratorToken type;
	JsonbParseState *st = NULL;
	text	   *out;
	bool		is_scalar = false;

	it = JsonbIteratorInit(&jsonb->root);
	is_scalar = it->isScalar;

	while ((type = JsonbIteratorNext(&it, &v, false)) != WJB_DONE)
	{
		if ((type == WJB_VALUE || type == WJB_ELEM) && v.type == jbvString)
		{
			out = transform_action(action_state, v.val.string.val, v.val.string.len);
			v.val.string.val = VARDATA_ANY(out);
			v.val.string.len = VARSIZE_ANY_EXHDR(out);
			res = pushJsonbValue(&st, type, type < WJB_BEGIN_ARRAY ? &v : NULL);
		}
		else
		{
			res = pushJsonbValue(&st, type, (type == WJB_KEY ||
											 type == WJB_VALUE ||
											 type == WJB_ELEM) ? &v : NULL);
		}
	}

	if (res->type == jbvArray)
		res->val.array.rawScalar = is_scalar;

	return JsonbValueToJsonb(res);
}