#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fn_oid; } ;
struct TYPE_4__ {int /*<<< orphan*/  eq_opr_finfo; TYPE_3__ cast_func_finfo; } ;
typedef  TYPE_1__ RI_CompareHashEntry ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  BoolGetDatum (int) ; 
 int /*<<< orphan*/  DEFAULT_COLLATION_OID ; 
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall3 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 TYPE_1__* ri_HashCompareOp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ri_AttributesEqual(Oid eq_opr, Oid typeid,
				   Datum oldvalue, Datum newvalue)
{
	RI_CompareHashEntry *entry = ri_HashCompareOp(eq_opr, typeid);

	/* Do we need to cast the values? */
	if (OidIsValid(entry->cast_func_finfo.fn_oid))
	{
		oldvalue = FunctionCall3(&entry->cast_func_finfo,
								 oldvalue,
								 Int32GetDatum(-1), /* typmod */
								 BoolGetDatum(false));	/* implicit coercion */
		newvalue = FunctionCall3(&entry->cast_func_finfo,
								 newvalue,
								 Int32GetDatum(-1), /* typmod */
								 BoolGetDatum(false));	/* implicit coercion */
	}

	/*
	 * Apply the comparison operator.
	 *
	 * Note: This function is part of a call stack that determines whether an
	 * update to a row is significant enough that it needs checking or action
	 * on the other side of a foreign-key constraint.  Therefore, the
	 * comparison here would need to be done with the collation of the *other*
	 * table.  For simplicity (e.g., we might not even have the other table
	 * open), we'll just use the default collation here, which could lead to
	 * some false negatives.  All this would break if we ever allow
	 * database-wide collations to be nondeterministic.
	 */
	return DatumGetBool(FunctionCall2Coll(&entry->eq_opr_finfo,
										  DEFAULT_COLLATION_OID,
										  oldvalue, newvalue));
}