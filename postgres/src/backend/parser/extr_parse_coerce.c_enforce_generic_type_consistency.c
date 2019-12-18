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
 scalar_t__ OidIsValid (scalar_t__) ; 
 scalar_t__ UNKNOWNOID ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char*,char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 char* format_type_be (scalar_t__) ; 
 scalar_t__ getBaseType (scalar_t__) ; 
 scalar_t__ get_array_type (scalar_t__) ; 
 scalar_t__ get_element_type (scalar_t__) ; 
 scalar_t__ get_range_subtype (scalar_t__) ; 
 scalar_t__ type_is_array_domain (scalar_t__) ; 
 int /*<<< orphan*/  type_is_enum (scalar_t__) ; 

Oid
enforce_generic_type_consistency(const Oid *actual_arg_types,
								 Oid *declared_arg_types,
								 int nargs,
								 Oid rettype,
								 bool allow_poly)
{
	int			j;
	bool		have_generics = false;
	bool		have_unknowns = false;
	Oid			elem_typeid = InvalidOid;
	Oid			array_typeid = InvalidOid;
	Oid			range_typeid = InvalidOid;
	Oid			array_typelem;
	Oid			range_typelem;
	bool		have_anyelement = (rettype == ANYELEMENTOID ||
								   rettype == ANYNONARRAYOID ||
								   rettype == ANYENUMOID);
	bool		have_anynonarray = (rettype == ANYNONARRAYOID);
	bool		have_anyenum = (rettype == ANYENUMOID);

	/*
	 * Loop through the arguments to see if we have any that are polymorphic.
	 * If so, require the actual types to be consistent.
	 */
	for (j = 0; j < nargs; j++)
	{
		Oid			decl_type = declared_arg_types[j];
		Oid			actual_type = actual_arg_types[j];

		if (decl_type == ANYELEMENTOID ||
			decl_type == ANYNONARRAYOID ||
			decl_type == ANYENUMOID)
		{
			have_generics = have_anyelement = true;
			if (decl_type == ANYNONARRAYOID)
				have_anynonarray = true;
			else if (decl_type == ANYENUMOID)
				have_anyenum = true;
			if (actual_type == UNKNOWNOID)
			{
				have_unknowns = true;
				continue;
			}
			if (allow_poly && decl_type == actual_type)
				continue;		/* no new information here */
			if (OidIsValid(elem_typeid) && actual_type != elem_typeid)
				ereport(ERROR,
						(errcode(ERRCODE_DATATYPE_MISMATCH),
						 errmsg("arguments declared \"anyelement\" are not all alike"),
						 errdetail("%s versus %s",
								   format_type_be(elem_typeid),
								   format_type_be(actual_type))));
			elem_typeid = actual_type;
		}
		else if (decl_type == ANYARRAYOID)
		{
			have_generics = true;
			if (actual_type == UNKNOWNOID)
			{
				have_unknowns = true;
				continue;
			}
			if (allow_poly && decl_type == actual_type)
				continue;		/* no new information here */
			actual_type = getBaseType(actual_type); /* flatten domains */
			if (OidIsValid(array_typeid) && actual_type != array_typeid)
				ereport(ERROR,
						(errcode(ERRCODE_DATATYPE_MISMATCH),
						 errmsg("arguments declared \"anyarray\" are not all alike"),
						 errdetail("%s versus %s",
								   format_type_be(array_typeid),
								   format_type_be(actual_type))));
			array_typeid = actual_type;
		}
		else if (decl_type == ANYRANGEOID)
		{
			have_generics = true;
			if (actual_type == UNKNOWNOID)
			{
				have_unknowns = true;
				continue;
			}
			if (allow_poly && decl_type == actual_type)
				continue;		/* no new information here */
			actual_type = getBaseType(actual_type); /* flatten domains */
			if (OidIsValid(range_typeid) && actual_type != range_typeid)
				ereport(ERROR,
						(errcode(ERRCODE_DATATYPE_MISMATCH),
						 errmsg("arguments declared \"anyrange\" are not all alike"),
						 errdetail("%s versus %s",
								   format_type_be(range_typeid),
								   format_type_be(actual_type))));
			range_typeid = actual_type;
		}
	}

	/*
	 * Fast Track: if none of the arguments are polymorphic, return the
	 * unmodified rettype.  We assume it can't be polymorphic either.
	 */
	if (!have_generics)
		return rettype;

	/* Get the element type based on the array type, if we have one */
	if (OidIsValid(array_typeid))
	{
		if (array_typeid == ANYARRAYOID && !have_anyelement)
		{
			/* Special case for ANYARRAY input: okay iff no ANYELEMENT */
			array_typelem = ANYELEMENTOID;
		}
		else
		{
			array_typelem = get_element_type(array_typeid);
			if (!OidIsValid(array_typelem))
				ereport(ERROR,
						(errcode(ERRCODE_DATATYPE_MISMATCH),
						 errmsg("argument declared %s is not an array but type %s",
								"anyarray", format_type_be(array_typeid))));
		}

		if (!OidIsValid(elem_typeid))
		{
			/*
			 * if we don't have an element type yet, use the one we just got
			 */
			elem_typeid = array_typelem;
		}
		else if (array_typelem != elem_typeid)
		{
			/* otherwise, they better match */
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("argument declared %s is not consistent with argument declared %s",
							"anyarray", "anyelement"),
					 errdetail("%s versus %s",
							   format_type_be(array_typeid),
							   format_type_be(elem_typeid))));
		}
	}

	/* Get the element type based on the range type, if we have one */
	if (OidIsValid(range_typeid))
	{
		if (range_typeid == ANYRANGEOID && !have_anyelement)
		{
			/* Special case for ANYRANGE input: okay iff no ANYELEMENT */
			range_typelem = ANYELEMENTOID;
		}
		else
		{
			range_typelem = get_range_subtype(range_typeid);
			if (!OidIsValid(range_typelem))
				ereport(ERROR,
						(errcode(ERRCODE_DATATYPE_MISMATCH),
						 errmsg("argument declared %s is not a range type but type %s",
								"anyrange",
								format_type_be(range_typeid))));
		}

		if (!OidIsValid(elem_typeid))
		{
			/*
			 * if we don't have an element type yet, use the one we just got
			 */
			elem_typeid = range_typelem;
		}
		else if (range_typelem != elem_typeid)
		{
			/* otherwise, they better match */
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("argument declared %s is not consistent with argument declared %s",
							"anyrange", "anyelement"),
					 errdetail("%s versus %s",
							   format_type_be(range_typeid),
							   format_type_be(elem_typeid))));
		}
	}

	if (!OidIsValid(elem_typeid))
	{
		if (allow_poly)
		{
			elem_typeid = ANYELEMENTOID;
			array_typeid = ANYARRAYOID;
			range_typeid = ANYRANGEOID;
		}
		else
		{
			/* Only way to get here is if all the generic args are UNKNOWN */
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("could not determine polymorphic type because input has type %s",
							"unknown")));
		}
	}

	if (have_anynonarray && elem_typeid != ANYELEMENTOID)
	{
		/* require the element type to not be an array or domain over array */
		if (type_is_array_domain(elem_typeid))
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("type matched to anynonarray is an array type: %s",
							format_type_be(elem_typeid))));
	}

	if (have_anyenum && elem_typeid != ANYELEMENTOID)
	{
		/* require the element type to be an enum */
		if (!type_is_enum(elem_typeid))
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("type matched to anyenum is not an enum type: %s",
							format_type_be(elem_typeid))));
	}

	/*
	 * If we had any unknown inputs, re-scan to assign correct types
	 */
	if (have_unknowns)
	{
		for (j = 0; j < nargs; j++)
		{
			Oid			decl_type = declared_arg_types[j];
			Oid			actual_type = actual_arg_types[j];

			if (actual_type != UNKNOWNOID)
				continue;

			if (decl_type == ANYELEMENTOID ||
				decl_type == ANYNONARRAYOID ||
				decl_type == ANYENUMOID)
				declared_arg_types[j] = elem_typeid;
			else if (decl_type == ANYARRAYOID)
			{
				if (!OidIsValid(array_typeid))
				{
					array_typeid = get_array_type(elem_typeid);
					if (!OidIsValid(array_typeid))
						ereport(ERROR,
								(errcode(ERRCODE_UNDEFINED_OBJECT),
								 errmsg("could not find array type for data type %s",
										format_type_be(elem_typeid))));
				}
				declared_arg_types[j] = array_typeid;
			}
			else if (decl_type == ANYRANGEOID)
			{
				if (!OidIsValid(range_typeid))
				{
					ereport(ERROR,
							(errcode(ERRCODE_UNDEFINED_OBJECT),
							 errmsg("could not find range type for data type %s",
									format_type_be(elem_typeid))));
				}
				declared_arg_types[j] = range_typeid;
			}
		}
	}

	/* if we return ANYARRAY use the appropriate argument type */
	if (rettype == ANYARRAYOID)
	{
		if (!OidIsValid(array_typeid))
		{
			array_typeid = get_array_type(elem_typeid);
			if (!OidIsValid(array_typeid))
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_OBJECT),
						 errmsg("could not find array type for data type %s",
								format_type_be(elem_typeid))));
		}
		return array_typeid;
	}

	/* if we return ANYRANGE use the appropriate argument type */
	if (rettype == ANYRANGEOID)
	{
		if (!OidIsValid(range_typeid))
		{
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("could not find range type for data type %s",
							format_type_be(elem_typeid))));
		}
		return range_typeid;
	}

	/* if we return ANYELEMENT use the appropriate argument type */
	if (rettype == ANYELEMENTOID ||
		rettype == ANYNONARRAYOID ||
		rettype == ANYENUMOID)
		return elem_typeid;

	/* we don't return a generic type; send back the original return type */
	return rettype;
}