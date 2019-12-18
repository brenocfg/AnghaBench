#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
struct TYPE_8__ {scalar_t__ names; scalar_t__ arrayBounds; int /*<<< orphan*/  location; scalar_t__ pct_type; int /*<<< orphan*/  typeOid; } ;
typedef  TYPE_1__ TypeName ;
typedef  int /*<<< orphan*/ * Type ;
struct TYPE_9__ {void* relname; void* schemaname; void* catalogname; } ;
typedef  TYPE_2__ RangeVar ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  ParseCallbackState ;
typedef  int /*<<< orphan*/  Oid ;
typedef  scalar_t__ HeapTuple ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_type_oid ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DeconstructQualifiedName (scalar_t__,char**,char**) ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_COLUMN ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetSysCacheOid2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (scalar_t__) ; 
 scalar_t__ InvalidAttrNumber ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LookupExplicitNamespace (char*,int) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  NameListToString (scalar_t__) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (char*) ; 
 int /*<<< orphan*/  RangeVarGetRelid (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPENAMENSP ; 
 int /*<<< orphan*/  TYPEOID ; 
 char* TypeNameToString (TYPE_1__ const*) ; 
 int /*<<< orphan*/  TypenameGetTypidExtended (char*,int) ; 
 int /*<<< orphan*/  cancel_parser_errposition_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,...) ; 
 void* format_type_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_array_type (int /*<<< orphan*/ ) ; 
 scalar_t__ get_attnum (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_atttype (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lfourth (scalar_t__) ; 
 int /*<<< orphan*/  linitial (scalar_t__) ; 
 int list_length (scalar_t__) ; 
 int /*<<< orphan*/  lsecond (scalar_t__) ; 
 int /*<<< orphan*/  lthird (scalar_t__) ; 
 TYPE_2__* makeRangeVar (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser_errposition (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_parser_errposition_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* strVal (int /*<<< orphan*/ ) ; 
 int typenameTypeMod (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *) ; 

Type
LookupTypeNameExtended(ParseState *pstate,
					   const TypeName *typeName, int32 *typmod_p,
					   bool temp_ok, bool missing_ok)
{
	Oid			typoid;
	HeapTuple	tup;
	int32		typmod;

	if (typeName->names == NIL)
	{
		/* We have the OID already if it's an internally generated TypeName */
		typoid = typeName->typeOid;
	}
	else if (typeName->pct_type)
	{
		/* Handle %TYPE reference to type of an existing field */
		RangeVar   *rel = makeRangeVar(NULL, NULL, typeName->location);
		char	   *field = NULL;
		Oid			relid;
		AttrNumber	attnum;

		/* deconstruct the name list */
		switch (list_length(typeName->names))
		{
			case 1:
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("improper %%TYPE reference (too few dotted names): %s",
								NameListToString(typeName->names)),
						 parser_errposition(pstate, typeName->location)));
				break;
			case 2:
				rel->relname = strVal(linitial(typeName->names));
				field = strVal(lsecond(typeName->names));
				break;
			case 3:
				rel->schemaname = strVal(linitial(typeName->names));
				rel->relname = strVal(lsecond(typeName->names));
				field = strVal(lthird(typeName->names));
				break;
			case 4:
				rel->catalogname = strVal(linitial(typeName->names));
				rel->schemaname = strVal(lsecond(typeName->names));
				rel->relname = strVal(lthird(typeName->names));
				field = strVal(lfourth(typeName->names));
				break;
			default:
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("improper %%TYPE reference (too many dotted names): %s",
								NameListToString(typeName->names)),
						 parser_errposition(pstate, typeName->location)));
				break;
		}

		/*
		 * Look up the field.
		 *
		 * XXX: As no lock is taken here, this might fail in the presence of
		 * concurrent DDL.  But taking a lock would carry a performance
		 * penalty and would also require a permissions check.
		 */
		relid = RangeVarGetRelid(rel, NoLock, missing_ok);
		attnum = get_attnum(relid, field);
		if (attnum == InvalidAttrNumber)
		{
			if (missing_ok)
				typoid = InvalidOid;
			else
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_COLUMN),
						 errmsg("column \"%s\" of relation \"%s\" does not exist",
								field, rel->relname),
						 parser_errposition(pstate, typeName->location)));
		}
		else
		{
			typoid = get_atttype(relid, attnum);

			/* this construct should never have an array indicator */
			Assert(typeName->arrayBounds == NIL);

			/* emit nuisance notice (intentionally not errposition'd) */
			ereport(NOTICE,
					(errmsg("type reference %s converted to %s",
							TypeNameToString(typeName),
							format_type_be(typoid))));
		}
	}
	else
	{
		/* Normal reference to a type name */
		char	   *schemaname;
		char	   *typname;

		/* deconstruct the name list */
		DeconstructQualifiedName(typeName->names, &schemaname, &typname);

		if (schemaname)
		{
			/* Look in specific schema only */
			Oid			namespaceId;
			ParseCallbackState pcbstate;

			setup_parser_errposition_callback(&pcbstate, pstate, typeName->location);

			namespaceId = LookupExplicitNamespace(schemaname, missing_ok);
			if (OidIsValid(namespaceId))
				typoid = GetSysCacheOid2(TYPENAMENSP, Anum_pg_type_oid,
										 PointerGetDatum(typname),
										 ObjectIdGetDatum(namespaceId));
			else
				typoid = InvalidOid;

			cancel_parser_errposition_callback(&pcbstate);
		}
		else
		{
			/* Unqualified type name, so search the search path */
			typoid = TypenameGetTypidExtended(typname, temp_ok);
		}

		/* If an array reference, return the array type instead */
		if (typeName->arrayBounds != NIL)
			typoid = get_array_type(typoid);
	}

	if (!OidIsValid(typoid))
	{
		if (typmod_p)
			*typmod_p = -1;
		return NULL;
	}

	tup = SearchSysCache1(TYPEOID, ObjectIdGetDatum(typoid));
	if (!HeapTupleIsValid(tup)) /* should not happen */
		elog(ERROR, "cache lookup failed for type %u", typoid);

	typmod = typenameTypeMod(pstate, typeName, (Type) tup);

	if (typmod_p)
		*typmod_p = typmod;

	return (Type) tup;
}