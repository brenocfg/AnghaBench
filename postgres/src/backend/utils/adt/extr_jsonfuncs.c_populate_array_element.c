#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * sizes; int /*<<< orphan*/  acxt; TYPE_1__* aio; int /*<<< orphan*/  astate; int /*<<< orphan*/  mcxt; } ;
struct TYPE_4__ {int /*<<< orphan*/  element_type; int /*<<< orphan*/  element_typmod; int /*<<< orphan*/  element_info; } ;
typedef  TYPE_2__ PopulateArrayContext ;
typedef  int /*<<< orphan*/  JsValue ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  accumArrayResult (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  populate_record_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void
populate_array_element(PopulateArrayContext *ctx, int ndim, JsValue *jsv)
{
	Datum		element;
	bool		element_isnull;

	/* populate the array element */
	element = populate_record_field(ctx->aio->element_info,
									ctx->aio->element_type,
									ctx->aio->element_typmod,
									NULL, ctx->mcxt, PointerGetDatum(NULL),
									jsv, &element_isnull);

	accumArrayResult(ctx->astate, element, element_isnull,
					 ctx->aio->element_type, ctx->acxt);

	Assert(ndim > 0);
	ctx->sizes[ndim - 1]++;		/* increment current dimension counter */
}