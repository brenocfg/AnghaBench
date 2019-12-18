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
struct TYPE_7__ {int ndims; scalar_t__ colname; int /*<<< orphan*/ * sizes; } ;
struct TYPE_6__ {scalar_t__ data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ PopulateArrayContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TEXT_REPRESENTATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 

__attribute__((used)) static void
populate_array_report_expected_array(PopulateArrayContext *ctx, int ndim)
{
	if (ndim <= 0)
	{
		if (ctx->colname)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
					 errmsg("expected JSON array"),
					 errhint("See the value of key \"%s\".", ctx->colname)));
		else
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
					 errmsg("expected JSON array")));
	}
	else
	{
		StringInfoData indices;
		int			i;

		initStringInfo(&indices);

		Assert(ctx->ndims > 0 && ndim < ctx->ndims);

		for (i = 0; i < ndim; i++)
			appendStringInfo(&indices, "[%d]", ctx->sizes[i]);

		if (ctx->colname)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
					 errmsg("expected JSON array"),
					 errhint("See the array element %s of key \"%s\".",
							 indices.data, ctx->colname)));
		else
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
					 errmsg("expected JSON array"),
					 errhint("See the array element %s.",
							 indices.data)));
	}
}