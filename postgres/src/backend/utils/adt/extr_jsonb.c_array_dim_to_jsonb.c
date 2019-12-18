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
struct TYPE_4__ {int /*<<< orphan*/  parseState; void* res; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  JsonbTypeCategory ;
typedef  TYPE_1__ JsonbInState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  WJB_BEGIN_ARRAY ; 
 int /*<<< orphan*/  WJB_END_ARRAY ; 
 int /*<<< orphan*/  datum_to_jsonb (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* pushJsonbValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
array_dim_to_jsonb(JsonbInState *result, int dim, int ndims, int *dims, Datum *vals,
				   bool *nulls, int *valcount, JsonbTypeCategory tcategory,
				   Oid outfuncoid)
{
	int			i;

	Assert(dim < ndims);

	result->res = pushJsonbValue(&result->parseState, WJB_BEGIN_ARRAY, NULL);

	for (i = 1; i <= dims[dim]; i++)
	{
		if (dim + 1 == ndims)
		{
			datum_to_jsonb(vals[*valcount], nulls[*valcount], result, tcategory,
						   outfuncoid, false);
			(*valcount)++;
		}
		else
		{
			array_dim_to_jsonb(result, dim + 1, ndims, dims, vals, nulls,
							   valcount, tcategory, outfuncoid);
		}
	}

	result->res = pushJsonbValue(&result->parseState, WJB_END_ARRAY, NULL);
}