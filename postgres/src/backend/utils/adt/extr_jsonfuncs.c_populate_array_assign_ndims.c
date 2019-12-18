#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ndims; int* dims; int /*<<< orphan*/  sizes; } ;
typedef  TYPE_1__ PopulateArrayContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int* palloc (int) ; 
 int /*<<< orphan*/  palloc0 (int) ; 
 int /*<<< orphan*/  populate_array_report_expected_array (TYPE_1__*,int) ; 

__attribute__((used)) static void
populate_array_assign_ndims(PopulateArrayContext *ctx, int ndims)
{
	int			i;

	Assert(ctx->ndims <= 0);

	if (ndims <= 0)
		populate_array_report_expected_array(ctx, ndims);

	ctx->ndims = ndims;
	ctx->dims = palloc(sizeof(int) * ndims);
	ctx->sizes = palloc0(sizeof(int) * ndims);

	for (i = 0; i < ndims; i++)
		ctx->dims[i] = -1;		/* dimensions are unknown yet */
}