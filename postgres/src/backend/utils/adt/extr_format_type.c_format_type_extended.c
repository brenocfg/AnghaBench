#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
typedef  int bits16 ;
struct TYPE_2__ {scalar_t__ typelem; char typstorage; int /*<<< orphan*/  typmodout; int /*<<< orphan*/  typname; int /*<<< orphan*/  typnamespace; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_type ;

/* Variables and functions */
#define  BITOID 143 
#define  BOOLOID 142 
#define  BPCHAROID 141 
 int /*<<< orphan*/  ERROR ; 
#define  FLOAT4OID 140 
#define  FLOAT8OID 139 
 int FORMAT_TYPE_ALLOW_INVALID ; 
 int FORMAT_TYPE_FORCE_QUALIFY ; 
 int FORMAT_TYPE_TYPEMOD_GIVEN ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
#define  INT2OID 138 
#define  INT4OID 137 
#define  INT8OID 136 
#define  INTERVALOID 135 
 scalar_t__ InvalidOid ; 
#define  NUMERICOID 134 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TIMEOID 133 
#define  TIMESTAMPOID 132 
#define  TIMESTAMPTZOID 131 
#define  TIMETZOID 130 
 int /*<<< orphan*/  TYPEOID ; 
 scalar_t__ TypeIsVisible (scalar_t__) ; 
#define  VARBITOID 129 
#define  VARCHAROID 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 char* get_namespace_name_or_temp (int /*<<< orphan*/ ) ; 
 char* printTypmod (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* psprintf (char*,char*) ; 
 char* pstrdup (char*) ; 
 char* quote_qualified_identifier (char*,char*) ; 

char *
format_type_extended(Oid type_oid, int32 typemod, bits16 flags)
{
	HeapTuple	tuple;
	Form_pg_type typeform;
	Oid			array_base_type;
	bool		is_array;
	char	   *buf;
	bool		with_typemod;

	if (type_oid == InvalidOid && (flags & FORMAT_TYPE_ALLOW_INVALID) != 0)
		return pstrdup("-");

	tuple = SearchSysCache1(TYPEOID, ObjectIdGetDatum(type_oid));
	if (!HeapTupleIsValid(tuple))
	{
		if ((flags & FORMAT_TYPE_ALLOW_INVALID) != 0)
			return pstrdup("???");
		else
			elog(ERROR, "cache lookup failed for type %u", type_oid);
	}
	typeform = (Form_pg_type) GETSTRUCT(tuple);

	/*
	 * Check if it's a regular (variable length) array type.  Fixed-length
	 * array types such as "name" shouldn't get deconstructed.  As of Postgres
	 * 8.1, rather than checking typlen we check the toast property, and don't
	 * deconstruct "plain storage" array types --- this is because we don't
	 * want to show oidvector as oid[].
	 */
	array_base_type = typeform->typelem;

	if (array_base_type != InvalidOid && typeform->typstorage != 'p')
	{
		/* Switch our attention to the array element type */
		ReleaseSysCache(tuple);
		tuple = SearchSysCache1(TYPEOID, ObjectIdGetDatum(array_base_type));
		if (!HeapTupleIsValid(tuple))
		{
			if ((flags & FORMAT_TYPE_ALLOW_INVALID) != 0)
				return pstrdup("???[]");
			else
				elog(ERROR, "cache lookup failed for type %u", type_oid);
		}
		typeform = (Form_pg_type) GETSTRUCT(tuple);
		type_oid = array_base_type;
		is_array = true;
	}
	else
		is_array = false;

	with_typemod = (flags & FORMAT_TYPE_TYPEMOD_GIVEN) != 0 && (typemod >= 0);

	/*
	 * See if we want to special-case the output for certain built-in types.
	 * Note that these special cases should all correspond to special
	 * productions in gram.y, to ensure that the type name will be taken as a
	 * system type, not a user type of the same name.
	 *
	 * If we do not provide a special-case output here, the type name will be
	 * handled the same way as a user type name --- in particular, it will be
	 * double-quoted if it matches any lexer keyword.  This behavior is
	 * essential for some cases, such as types "bit" and "char".
	 */
	buf = NULL;					/* flag for no special case */

	switch (type_oid)
	{
		case BITOID:
			if (with_typemod)
				buf = printTypmod("bit", typemod, typeform->typmodout);
			else if ((flags & FORMAT_TYPE_TYPEMOD_GIVEN) != 0)
			{
				/*
				 * bit with typmod -1 is not the same as BIT, which means
				 * BIT(1) per SQL spec.  Report it as the quoted typename so
				 * that parser will not assign a bogus typmod.
				 */
			}
			else
				buf = pstrdup("bit");
			break;

		case BOOLOID:
			buf = pstrdup("boolean");
			break;

		case BPCHAROID:
			if (with_typemod)
				buf = printTypmod("character", typemod, typeform->typmodout);
			else if ((flags & FORMAT_TYPE_TYPEMOD_GIVEN) != 0)
			{
				/*
				 * bpchar with typmod -1 is not the same as CHARACTER, which
				 * means CHARACTER(1) per SQL spec.  Report it as bpchar so
				 * that parser will not assign a bogus typmod.
				 */
			}
			else
				buf = pstrdup("character");
			break;

		case FLOAT4OID:
			buf = pstrdup("real");
			break;

		case FLOAT8OID:
			buf = pstrdup("double precision");
			break;

		case INT2OID:
			buf = pstrdup("smallint");
			break;

		case INT4OID:
			buf = pstrdup("integer");
			break;

		case INT8OID:
			buf = pstrdup("bigint");
			break;

		case NUMERICOID:
			if (with_typemod)
				buf = printTypmod("numeric", typemod, typeform->typmodout);
			else
				buf = pstrdup("numeric");
			break;

		case INTERVALOID:
			if (with_typemod)
				buf = printTypmod("interval", typemod, typeform->typmodout);
			else
				buf = pstrdup("interval");
			break;

		case TIMEOID:
			if (with_typemod)
				buf = printTypmod("time", typemod, typeform->typmodout);
			else
				buf = pstrdup("time without time zone");
			break;

		case TIMETZOID:
			if (with_typemod)
				buf = printTypmod("time", typemod, typeform->typmodout);
			else
				buf = pstrdup("time with time zone");
			break;

		case TIMESTAMPOID:
			if (with_typemod)
				buf = printTypmod("timestamp", typemod, typeform->typmodout);
			else
				buf = pstrdup("timestamp without time zone");
			break;

		case TIMESTAMPTZOID:
			if (with_typemod)
				buf = printTypmod("timestamp", typemod, typeform->typmodout);
			else
				buf = pstrdup("timestamp with time zone");
			break;

		case VARBITOID:
			if (with_typemod)
				buf = printTypmod("bit varying", typemod, typeform->typmodout);
			else
				buf = pstrdup("bit varying");
			break;

		case VARCHAROID:
			if (with_typemod)
				buf = printTypmod("character varying", typemod, typeform->typmodout);
			else
				buf = pstrdup("character varying");
			break;
	}

	if (buf == NULL)
	{
		/*
		 * Default handling: report the name as it appears in the catalog.
		 * Here, we must qualify the name if it is not visible in the search
		 * path or if caller requests it; and we must double-quote it if it's
		 * not a standard identifier or if it matches any keyword.
		 */
		char	   *nspname;
		char	   *typname;

		if ((flags & FORMAT_TYPE_FORCE_QUALIFY) == 0 &&
			TypeIsVisible(type_oid))
			nspname = NULL;
		else
			nspname = get_namespace_name_or_temp(typeform->typnamespace);

		typname = NameStr(typeform->typname);

		buf = quote_qualified_identifier(nspname, typname);

		if (with_typemod)
			buf = printTypmod(buf, typemod, typeform->typmodout);
	}

	if (is_array)
		buf = psprintf("%s[]", buf);

	ReleaseSysCache(tuple);

	return buf;
}