#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  TypeName ;
struct TYPE_6__ {int const typtype; scalar_t__ domainBaseType; scalar_t__ tupDesc_identifier; int /*<<< orphan*/ * tupDesc; } ;
typedef  TYPE_1__ TypeCacheEntry ;
struct TYPE_8__ {scalar_t__ oid; int typtype; int typlen; char typstorage; int /*<<< orphan*/  typbasetype; int /*<<< orphan*/  typelem; int /*<<< orphan*/  typcollation; int /*<<< orphan*/  typbyval; int /*<<< orphan*/  typname; int /*<<< orphan*/  typisdefined; } ;
struct TYPE_7__ {scalar_t__ typoid; scalar_t__ ttype; int typlen; int typtype; int typisarray; scalar_t__ tupdesc_id; TYPE_1__* tcache; int /*<<< orphan*/ * origtypname; int /*<<< orphan*/  atttypmod; int /*<<< orphan*/  collation; int /*<<< orphan*/  typbyval; int /*<<< orphan*/  typname; } ;
typedef  TYPE_2__ PLpgSQL_type ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_type ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ PLPGSQL_TTYPE_PSEUDO ; 
 scalar_t__ PLPGSQL_TTYPE_REC ; 
 void* PLPGSQL_TTYPE_SCALAR ; 
 scalar_t__ RECORDOID ; 
 int TYPECACHE_DOMAIN_BASE_INFO ; 
 int TYPECACHE_TUPDESC ; 
#define  TYPTYPE_BASE 133 
#define  TYPTYPE_COMPOSITE 132 
#define  TYPTYPE_DOMAIN 131 
#define  TYPTYPE_ENUM 130 
#define  TYPTYPE_PSEUDO 129 
#define  TYPTYPE_RANGE 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (scalar_t__) ; 
 int /*<<< orphan*/  get_base_element_type (int /*<<< orphan*/ ) ; 
 TYPE_1__* lookup_type_cache (scalar_t__,int) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_is_rowtype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PLpgSQL_type *
build_datatype(HeapTuple typeTup, int32 typmod,
			   Oid collation, TypeName *origtypname)
{
	Form_pg_type typeStruct = (Form_pg_type) GETSTRUCT(typeTup);
	PLpgSQL_type *typ;

	if (!typeStruct->typisdefined)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("type \"%s\" is only a shell",
						NameStr(typeStruct->typname))));

	typ = (PLpgSQL_type *) palloc(sizeof(PLpgSQL_type));

	typ->typname = pstrdup(NameStr(typeStruct->typname));
	typ->typoid = typeStruct->oid;
	switch (typeStruct->typtype)
	{
		case TYPTYPE_BASE:
		case TYPTYPE_ENUM:
		case TYPTYPE_RANGE:
			typ->ttype = PLPGSQL_TTYPE_SCALAR;
			break;
		case TYPTYPE_COMPOSITE:
			typ->ttype = PLPGSQL_TTYPE_REC;
			break;
		case TYPTYPE_DOMAIN:
			if (type_is_rowtype(typeStruct->typbasetype))
				typ->ttype = PLPGSQL_TTYPE_REC;
			else
				typ->ttype = PLPGSQL_TTYPE_SCALAR;
			break;
		case TYPTYPE_PSEUDO:
			if (typ->typoid == RECORDOID)
				typ->ttype = PLPGSQL_TTYPE_REC;
			else
				typ->ttype = PLPGSQL_TTYPE_PSEUDO;
			break;
		default:
			elog(ERROR, "unrecognized typtype: %d",
				 (int) typeStruct->typtype);
			break;
	}
	typ->typlen = typeStruct->typlen;
	typ->typbyval = typeStruct->typbyval;
	typ->typtype = typeStruct->typtype;
	typ->collation = typeStruct->typcollation;
	if (OidIsValid(collation) && OidIsValid(typ->collation))
		typ->collation = collation;
	/* Detect if type is true array, or domain thereof */
	/* NB: this is only used to decide whether to apply expand_array */
	if (typeStruct->typtype == TYPTYPE_BASE)
	{
		/*
		 * This test should include what get_element_type() checks.  We also
		 * disallow non-toastable array types (i.e. oidvector and int2vector).
		 */
		typ->typisarray = (typeStruct->typlen == -1 &&
						   OidIsValid(typeStruct->typelem) &&
						   typeStruct->typstorage != 'p');
	}
	else if (typeStruct->typtype == TYPTYPE_DOMAIN)
	{
		/* we can short-circuit looking up base types if it's not varlena */
		typ->typisarray = (typeStruct->typlen == -1 &&
						   typeStruct->typstorage != 'p' &&
						   OidIsValid(get_base_element_type(typeStruct->typbasetype)));
	}
	else
		typ->typisarray = false;
	typ->atttypmod = typmod;

	/*
	 * If it's a named composite type (or domain over one), find the typcache
	 * entry and record the current tupdesc ID, so we can detect changes
	 * (including drops).  We don't currently support on-the-fly replacement
	 * of non-composite types, else we might want to do this for them too.
	 */
	if (typ->ttype == PLPGSQL_TTYPE_REC && typ->typoid != RECORDOID)
	{
		TypeCacheEntry *typentry;

		typentry = lookup_type_cache(typ->typoid,
									 TYPECACHE_TUPDESC |
									 TYPECACHE_DOMAIN_BASE_INFO);
		if (typentry->typtype == TYPTYPE_DOMAIN)
			typentry = lookup_type_cache(typentry->domainBaseType,
										 TYPECACHE_TUPDESC);
		if (typentry->tupDesc == NULL)
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("type %s is not composite",
							format_type_be(typ->typoid))));

		typ->origtypname = origtypname;
		typ->tcache = typentry;
		typ->tupdesc_id = typentry->tupDesc_identifier;
	}
	else
	{
		typ->origtypname = NULL;
		typ->tcache = NULL;
		typ->tupdesc_id = 0;
	}

	return typ;
}