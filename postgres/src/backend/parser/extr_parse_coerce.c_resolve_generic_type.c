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

/* Variables and functions */
 scalar_t__ ANYARRAYOID ; 
 scalar_t__ ANYELEMENTOID ; 
 scalar_t__ ANYENUMOID ; 
 scalar_t__ ANYNONARRAYOID ; 
 scalar_t__ ANYRANGEOID ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,...) ; 
 int /*<<< orphan*/  format_type_be (scalar_t__) ; 
 scalar_t__ getBaseType (scalar_t__) ; 
 scalar_t__ get_array_type (scalar_t__) ; 
 scalar_t__ get_element_type (scalar_t__) ; 
 scalar_t__ get_range_subtype (scalar_t__) ; 

Oid
resolve_generic_type(Oid declared_type,
					 Oid context_actual_type,
					 Oid context_declared_type)
{
	if (declared_type == ANYARRAYOID)
	{
		if (context_declared_type == ANYARRAYOID)
		{
			/*
			 * Use actual type, but it must be an array; or if it's a domain
			 * over array, use the base array type.
			 */
			Oid			context_base_type = getBaseType(context_actual_type);
			Oid			array_typelem = get_element_type(context_base_type);

			if (!OidIsValid(array_typelem))
				ereport(ERROR,
						(errcode(ERRCODE_DATATYPE_MISMATCH),
						 errmsg("argument declared %s is not an array but type %s",
								"anyarray", format_type_be(context_base_type))));
			return context_base_type;
		}
		else if (context_declared_type == ANYELEMENTOID ||
				 context_declared_type == ANYNONARRAYOID ||
				 context_declared_type == ANYENUMOID ||
				 context_declared_type == ANYRANGEOID)
		{
			/* Use the array type corresponding to actual type */
			Oid			array_typeid = get_array_type(context_actual_type);

			if (!OidIsValid(array_typeid))
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_OBJECT),
						 errmsg("could not find array type for data type %s",
								format_type_be(context_actual_type))));
			return array_typeid;
		}
	}
	else if (declared_type == ANYELEMENTOID ||
			 declared_type == ANYNONARRAYOID ||
			 declared_type == ANYENUMOID ||
			 declared_type == ANYRANGEOID)
	{
		if (context_declared_type == ANYARRAYOID)
		{
			/* Use the element type corresponding to actual type */
			Oid			context_base_type = getBaseType(context_actual_type);
			Oid			array_typelem = get_element_type(context_base_type);

			if (!OidIsValid(array_typelem))
				ereport(ERROR,
						(errcode(ERRCODE_DATATYPE_MISMATCH),
						 errmsg("argument declared %s is not an array but type %s",
								"anyarray", format_type_be(context_base_type))));
			return array_typelem;
		}
		else if (context_declared_type == ANYRANGEOID)
		{
			/* Use the element type corresponding to actual type */
			Oid			context_base_type = getBaseType(context_actual_type);
			Oid			range_typelem = get_range_subtype(context_base_type);

			if (!OidIsValid(range_typelem))
				ereport(ERROR,
						(errcode(ERRCODE_DATATYPE_MISMATCH),
						 errmsg("argument declared %s is not a range type but type %s",
								"anyrange", format_type_be(context_base_type))));
			return range_typelem;
		}
		else if (context_declared_type == ANYELEMENTOID ||
				 context_declared_type == ANYNONARRAYOID ||
				 context_declared_type == ANYENUMOID)
		{
			/* Use the actual type; it doesn't matter if array or not */
			return context_actual_type;
		}
	}
	else
	{
		/* declared_type isn't polymorphic, so return it as-is */
		return declared_type;
	}
	/* If we get here, declared_type is polymorphic and context isn't */
	/* NB: this is a calling-code logic error, not a user error */
	elog(ERROR, "could not determine polymorphic type because context isn't polymorphic");
	return InvalidOid;			/* keep compiler quiet */
}