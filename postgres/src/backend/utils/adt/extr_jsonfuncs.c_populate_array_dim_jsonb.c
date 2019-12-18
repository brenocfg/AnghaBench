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
struct TYPE_17__ {TYPE_5__* jsonb; } ;
struct TYPE_20__ {int is_json; TYPE_3__ val; } ;
struct TYPE_15__ {int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {TYPE_1__ binary; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_2__ val; } ;
struct TYPE_18__ {int ndims; scalar_t__ dims; } ;
typedef  TYPE_4__ PopulateArrayContext ;
typedef  TYPE_5__ JsonbValue ;
typedef  scalar_t__ JsonbIteratorToken ;
typedef  int /*<<< orphan*/  JsonbIterator ;
typedef  int /*<<< orphan*/  JsonbContainer ;
typedef  TYPE_6__ JsValue ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  JsonContainerIsArray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonContainerIsScalar (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonbIteratorInit (int /*<<< orphan*/ *) ; 
 scalar_t__ JsonbIteratorNext (int /*<<< orphan*/ **,TYPE_5__*,int) ; 
 scalar_t__ WJB_BEGIN_ARRAY ; 
 scalar_t__ WJB_DONE ; 
 scalar_t__ WJB_ELEM ; 
 scalar_t__ WJB_END_ARRAY ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 scalar_t__ jbvBinary ; 
 int /*<<< orphan*/  populate_array_assign_ndims (TYPE_4__*,int) ; 
 int /*<<< orphan*/  populate_array_check_dimension (TYPE_4__*,int) ; 
 int /*<<< orphan*/  populate_array_element (TYPE_4__*,int,TYPE_6__*) ; 
 int /*<<< orphan*/  populate_array_report_expected_array (TYPE_4__*,int) ; 

__attribute__((used)) static void
populate_array_dim_jsonb(PopulateArrayContext *ctx, /* context */
						 JsonbValue *jbv,	/* jsonb sub-array */
						 int ndim)	/* current dimension */
{
	JsonbContainer *jbc = jbv->val.binary.data;
	JsonbIterator *it;
	JsonbIteratorToken tok;
	JsonbValue	val;
	JsValue		jsv;

	check_stack_depth();

	if (jbv->type != jbvBinary || !JsonContainerIsArray(jbc))
		populate_array_report_expected_array(ctx, ndim - 1);

	Assert(!JsonContainerIsScalar(jbc));

	it = JsonbIteratorInit(jbc);

	tok = JsonbIteratorNext(&it, &val, true);
	Assert(tok == WJB_BEGIN_ARRAY);

	tok = JsonbIteratorNext(&it, &val, true);

	/*
	 * If the number of dimensions is not yet known and we have found end of
	 * the array, or the first child element is not an array, then assign the
	 * number of dimensions now.
	 */
	if (ctx->ndims <= 0 &&
		(tok == WJB_END_ARRAY ||
		 (tok == WJB_ELEM &&
		  (val.type != jbvBinary ||
		   !JsonContainerIsArray(val.val.binary.data)))))
		populate_array_assign_ndims(ctx, ndim);

	jsv.is_json = false;
	jsv.val.jsonb = &val;

	/* process all the array elements */
	while (tok == WJB_ELEM)
	{
		/*
		 * Recurse only if the dimensions of dimensions is still unknown or if
		 * it is not the innermost dimension.
		 */
		if (ctx->ndims > 0 && ndim >= ctx->ndims)
			populate_array_element(ctx, ndim, &jsv);
		else
		{
			/* populate child sub-array */
			populate_array_dim_jsonb(ctx, &val, ndim + 1);

			/* number of dimensions should be already known */
			Assert(ctx->ndims > 0 && ctx->dims);

			populate_array_check_dimension(ctx, ndim);
		}

		tok = JsonbIteratorNext(&it, &val, true);
	}

	Assert(tok == WJB_END_ARRAY);

	/* free iterator, iterating until WJB_DONE */
	tok = JsonbIteratorNext(&it, &val, true);
	Assert(tok == WJB_DONE && !it);
}