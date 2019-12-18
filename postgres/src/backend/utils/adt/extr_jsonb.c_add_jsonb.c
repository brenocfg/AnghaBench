#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  JsonbTypeCategory ;
typedef  int /*<<< orphan*/  JsonbInState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  JSONBTYPE_NULL ; 
 int /*<<< orphan*/  datum_to_jsonb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  jsonb_categorize_type (scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static void
add_jsonb(Datum val, bool is_null, JsonbInState *result,
		  Oid val_type, bool key_scalar)
{
	JsonbTypeCategory tcategory;
	Oid			outfuncoid;

	if (val_type == InvalidOid)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("could not determine input data type")));

	if (is_null)
	{
		tcategory = JSONBTYPE_NULL;
		outfuncoid = InvalidOid;
	}
	else
		jsonb_categorize_type(val_type,
							  &tcategory, &outfuncoid);

	datum_to_jsonb(val, is_null, result, tcategory, outfuncoid, key_scalar);
}