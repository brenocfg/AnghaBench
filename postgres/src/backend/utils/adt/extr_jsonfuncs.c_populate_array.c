#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  element_type; } ;
struct TYPE_10__ {scalar_t__ len; int /*<<< orphan*/  str; } ;
struct TYPE_11__ {int /*<<< orphan*/  jsonb; TYPE_1__ json; } ;
struct TYPE_13__ {TYPE_2__ val; scalar_t__ is_json; } ;
struct TYPE_12__ {char const* colname; int ndims; int* dims; int* sizes; int /*<<< orphan*/  acxt; int /*<<< orphan*/  astate; int /*<<< orphan*/  mcxt; TYPE_5__* aio; } ;
typedef  TYPE_3__ PopulateArrayContext ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_4__ JsValue ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_5__ ArrayIOData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  initArrayResult (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  makeMdArrayResult (int /*<<< orphan*/ ,int,int*,int*,int /*<<< orphan*/ ,int) ; 
 int* palloc (int) ; 
 int /*<<< orphan*/  pfree (int*) ; 
 int /*<<< orphan*/  populate_array_dim_jsonb (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  populate_array_json (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Datum
populate_array(ArrayIOData *aio,
			   const char *colname,
			   MemoryContext mcxt,
			   JsValue *jsv)
{
	PopulateArrayContext ctx;
	Datum		result;
	int		   *lbs;
	int			i;

	ctx.aio = aio;
	ctx.mcxt = mcxt;
	ctx.acxt = CurrentMemoryContext;
	ctx.astate = initArrayResult(aio->element_type, ctx.acxt, true);
	ctx.colname = colname;
	ctx.ndims = 0;				/* unknown yet */
	ctx.dims = NULL;
	ctx.sizes = NULL;

	if (jsv->is_json)
		populate_array_json(&ctx, jsv->val.json.str,
							jsv->val.json.len >= 0 ? jsv->val.json.len
							: strlen(jsv->val.json.str));
	else
	{
		populate_array_dim_jsonb(&ctx, jsv->val.jsonb, 1);
		ctx.dims[0] = ctx.sizes[0];
	}

	Assert(ctx.ndims > 0);

	lbs = palloc(sizeof(int) * ctx.ndims);

	for (i = 0; i < ctx.ndims; i++)
		lbs[i] = 1;

	result = makeMdArrayResult(ctx.astate, ctx.ndims, ctx.dims, lbs,
							   ctx.acxt, true);

	pfree(ctx.dims);
	pfree(ctx.sizes);
	pfree(lbs);

	return result;
}