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
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_4__ {int /*<<< orphan*/  parseState; void* res; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  JsonbTypeCategory ;
typedef  TYPE_1__ JsonbInState ;
typedef  int Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARR_ELEMTYPE (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 int ArrayGetNItems (int,int*) ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (int) ; 
 int /*<<< orphan*/  WJB_BEGIN_ARRAY ; 
 int /*<<< orphan*/  WJB_END_ARRAY ; 
 int /*<<< orphan*/  array_dim_to_jsonb (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int*,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char,int**,int**,int*) ; 
 int /*<<< orphan*/  get_typlenbyvalalign (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,char*) ; 
 int /*<<< orphan*/  jsonb_categorize_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (int*) ; 
 void* pushJsonbValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
array_to_jsonb_internal(Datum array, JsonbInState *result)
{
	ArrayType  *v = DatumGetArrayTypeP(array);
	Oid			element_type = ARR_ELEMTYPE(v);
	int		   *dim;
	int			ndim;
	int			nitems;
	int			count = 0;
	Datum	   *elements;
	bool	   *nulls;
	int16		typlen;
	bool		typbyval;
	char		typalign;
	JsonbTypeCategory tcategory;
	Oid			outfuncoid;

	ndim = ARR_NDIM(v);
	dim = ARR_DIMS(v);
	nitems = ArrayGetNItems(ndim, dim);

	if (nitems <= 0)
	{
		result->res = pushJsonbValue(&result->parseState, WJB_BEGIN_ARRAY, NULL);
		result->res = pushJsonbValue(&result->parseState, WJB_END_ARRAY, NULL);
		return;
	}

	get_typlenbyvalalign(element_type,
						 &typlen, &typbyval, &typalign);

	jsonb_categorize_type(element_type,
						  &tcategory, &outfuncoid);

	deconstruct_array(v, element_type, typlen, typbyval,
					  typalign, &elements, &nulls,
					  &nitems);

	array_dim_to_jsonb(result, 0, ndim, dim, elements, nulls, &count, tcategory,
					   outfuncoid);

	pfree(elements);
	pfree(nulls);
}