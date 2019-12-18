#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int dim1; int* values; } ;
typedef  TYPE_1__ oidvector ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_12__ {int atttypid; int /*<<< orphan*/  attname; } ;
struct TYPE_11__ {int natts; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_3__* Form_pg_attribute ;

/* Variables and functions */
#define  ANYARRAYOID 132 
#define  ANYELEMENTOID 131 
#define  ANYENUMOID 130 
#define  ANYNONARRAYOID 129 
#define  ANYRANGEOID 128 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 TYPE_3__* TupleDescAttr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  TupleDescInitEntry (TYPE_2__*,int,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TupleDescInitEntryCollation (TYPE_2__*,int,scalar_t__) ; 
 scalar_t__ exprInputCollation (int /*<<< orphan*/ *) ; 
 scalar_t__ get_call_expr_argtype (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_typcollation (scalar_t__) ; 
 scalar_t__ resolve_generic_type (int const,scalar_t__,int const) ; 
 scalar_t__ type_is_array (scalar_t__) ; 
 int /*<<< orphan*/  type_is_enum (scalar_t__) ; 

__attribute__((used)) static bool
resolve_polymorphic_tupdesc(TupleDesc tupdesc, oidvector *declared_args,
							Node *call_expr)
{
	int			natts = tupdesc->natts;
	int			nargs = declared_args->dim1;
	bool		have_anyelement_result = false;
	bool		have_anyarray_result = false;
	bool		have_anyrange_result = false;
	bool		have_anynonarray = false;
	bool		have_anyenum = false;
	Oid			anyelement_type = InvalidOid;
	Oid			anyarray_type = InvalidOid;
	Oid			anyrange_type = InvalidOid;
	Oid			anycollation = InvalidOid;
	int			i;

	/* See if there are any polymorphic outputs; quick out if not */
	for (i = 0; i < natts; i++)
	{
		switch (TupleDescAttr(tupdesc, i)->atttypid)
		{
			case ANYELEMENTOID:
				have_anyelement_result = true;
				break;
			case ANYARRAYOID:
				have_anyarray_result = true;
				break;
			case ANYNONARRAYOID:
				have_anyelement_result = true;
				have_anynonarray = true;
				break;
			case ANYENUMOID:
				have_anyelement_result = true;
				have_anyenum = true;
				break;
			case ANYRANGEOID:
				have_anyrange_result = true;
				break;
			default:
				break;
		}
	}
	if (!have_anyelement_result && !have_anyarray_result &&
		!have_anyrange_result)
		return true;

	/*
	 * Otherwise, extract actual datatype(s) from input arguments.  (We assume
	 * the parser already validated consistency of the arguments.)
	 */
	if (!call_expr)
		return false;			/* no hope */

	for (i = 0; i < nargs; i++)
	{
		switch (declared_args->values[i])
		{
			case ANYELEMENTOID:
			case ANYNONARRAYOID:
			case ANYENUMOID:
				if (!OidIsValid(anyelement_type))
					anyelement_type = get_call_expr_argtype(call_expr, i);
				break;
			case ANYARRAYOID:
				if (!OidIsValid(anyarray_type))
					anyarray_type = get_call_expr_argtype(call_expr, i);
				break;
			case ANYRANGEOID:
				if (!OidIsValid(anyrange_type))
					anyrange_type = get_call_expr_argtype(call_expr, i);
				break;
			default:
				break;
		}
	}

	/* If nothing found, parser messed up */
	if (!OidIsValid(anyelement_type) && !OidIsValid(anyarray_type) &&
		!OidIsValid(anyrange_type))
		return false;

	/* If needed, deduce one polymorphic type from others */
	if (have_anyelement_result && !OidIsValid(anyelement_type))
	{
		if (OidIsValid(anyarray_type))
			anyelement_type = resolve_generic_type(ANYELEMENTOID,
												   anyarray_type,
												   ANYARRAYOID);
		if (OidIsValid(anyrange_type))
		{
			Oid			subtype = resolve_generic_type(ANYELEMENTOID,
													   anyrange_type,
													   ANYRANGEOID);

			/* check for inconsistent array and range results */
			if (OidIsValid(anyelement_type) && anyelement_type != subtype)
				return false;
			anyelement_type = subtype;
		}
	}

	if (have_anyarray_result && !OidIsValid(anyarray_type))
		anyarray_type = resolve_generic_type(ANYARRAYOID,
											 anyelement_type,
											 ANYELEMENTOID);

	/*
	 * We can't deduce a range type from other polymorphic inputs, because
	 * there may be multiple range types for the same subtype.
	 */
	if (have_anyrange_result && !OidIsValid(anyrange_type))
		return false;

	/* Enforce ANYNONARRAY if needed */
	if (have_anynonarray && type_is_array(anyelement_type))
		return false;

	/* Enforce ANYENUM if needed */
	if (have_anyenum && !type_is_enum(anyelement_type))
		return false;

	/*
	 * Identify the collation to use for polymorphic OUT parameters. (It'll
	 * necessarily be the same for both anyelement and anyarray.)  Note that
	 * range types are not collatable, so any possible internal collation of a
	 * range type is not considered here.
	 */
	if (OidIsValid(anyelement_type))
		anycollation = get_typcollation(anyelement_type);
	else if (OidIsValid(anyarray_type))
		anycollation = get_typcollation(anyarray_type);

	if (OidIsValid(anycollation))
	{
		/*
		 * The types are collatable, so consider whether to use a nondefault
		 * collation.  We do so if we can identify the input collation used
		 * for the function.
		 */
		Oid			inputcollation = exprInputCollation(call_expr);

		if (OidIsValid(inputcollation))
			anycollation = inputcollation;
	}

	/* And finally replace the tuple column types as needed */
	for (i = 0; i < natts; i++)
	{
		Form_pg_attribute att = TupleDescAttr(tupdesc, i);

		switch (att->atttypid)
		{
			case ANYELEMENTOID:
			case ANYNONARRAYOID:
			case ANYENUMOID:
				TupleDescInitEntry(tupdesc, i + 1,
								   NameStr(att->attname),
								   anyelement_type,
								   -1,
								   0);
				TupleDescInitEntryCollation(tupdesc, i + 1, anycollation);
				break;
			case ANYARRAYOID:
				TupleDescInitEntry(tupdesc, i + 1,
								   NameStr(att->attname),
								   anyarray_type,
								   -1,
								   0);
				TupleDescInitEntryCollation(tupdesc, i + 1, anycollation);
				break;
			case ANYRANGEOID:
				TupleDescInitEntry(tupdesc, i + 1,
								   NameStr(att->attname),
								   anyrange_type,
								   -1,
								   0);
				/* no collation should be attached to a range type */
				break;
			default:
				break;
		}
	}

	return true;
}