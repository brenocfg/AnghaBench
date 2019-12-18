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
typedef  int int32 ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  PG_DETOAST_DATUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_GETARG_DATUM (int /*<<< orphan*/ ) ; 
 scalar_t__ PG_GETARG_POINTER (int) ; 
 int /*<<< orphan*/  PG_RETURN_POINTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static Datum
gin_btree_extract_value(FunctionCallInfo fcinfo, bool is_varlena)
{
	Datum		datum = PG_GETARG_DATUM(0);
	int32	   *nentries = (int32 *) PG_GETARG_POINTER(1);
	Datum	   *entries = (Datum *) palloc(sizeof(Datum));

	if (is_varlena)
		datum = PointerGetDatum(PG_DETOAST_DATUM(datum));
	entries[0] = datum;
	*nentries = 1;

	PG_RETURN_POINTER(entries);
}