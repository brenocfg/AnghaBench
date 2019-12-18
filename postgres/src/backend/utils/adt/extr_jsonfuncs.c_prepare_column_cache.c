#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* int32 ;
struct TYPE_13__ {int /*<<< orphan*/  typiofunc; int /*<<< orphan*/  typioparam; } ;
struct TYPE_11__ {void* element_typmod; int /*<<< orphan*/  element_type; void* element_info; } ;
struct TYPE_10__ {int /*<<< orphan*/ * domain_info; void* base_typmod; scalar_t__ base_typid; int /*<<< orphan*/ * tupdesc; int /*<<< orphan*/ * record_io; } ;
struct TYPE_9__ {int /*<<< orphan*/ * domain_info; void* base_io; void* base_typmod; scalar_t__ base_typid; } ;
struct TYPE_12__ {TYPE_3__ array; TYPE_2__ composite; TYPE_1__ domain; } ;
struct TYPE_15__ {TYPE_5__ scalar_io; int /*<<< orphan*/  typcat; TYPE_4__ io; void* typmod; scalar_t__ typid; } ;
struct TYPE_14__ {scalar_t__ typtype; int typlen; int /*<<< orphan*/  typelem; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_6__* Form_pg_type ;
typedef  TYPE_7__ ColumnIOData ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 void* MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ RECORDOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPECAT_ARRAY ; 
 int /*<<< orphan*/  TYPECAT_COMPOSITE ; 
 int /*<<< orphan*/  TYPECAT_COMPOSITE_DOMAIN ; 
 int /*<<< orphan*/  TYPECAT_DOMAIN ; 
 int /*<<< orphan*/  TYPECAT_SCALAR ; 
 int /*<<< orphan*/  TYPEOID ; 
 scalar_t__ TYPTYPE_COMPOSITE ; 
 scalar_t__ TYPTYPE_DOMAIN ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  fmgr_info_cxt (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ getBaseTypeAndTypmod (scalar_t__,void**) ; 
 int /*<<< orphan*/  getTypeInputInfo (scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ get_typtype (scalar_t__) ; 

__attribute__((used)) static void
prepare_column_cache(ColumnIOData *column,
					 Oid typid,
					 int32 typmod,
					 MemoryContext mcxt,
					 bool need_scalar)
{
	HeapTuple	tup;
	Form_pg_type type;

	column->typid = typid;
	column->typmod = typmod;

	tup = SearchSysCache1(TYPEOID, ObjectIdGetDatum(typid));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for type %u", typid);

	type = (Form_pg_type) GETSTRUCT(tup);

	if (type->typtype == TYPTYPE_DOMAIN)
	{
		/*
		 * We can move directly to the bottom base type; domain_check() will
		 * take care of checking all constraints for a stack of domains.
		 */
		Oid			base_typid;
		int32		base_typmod = typmod;

		base_typid = getBaseTypeAndTypmod(typid, &base_typmod);
		if (get_typtype(base_typid) == TYPTYPE_COMPOSITE)
		{
			/* domain over composite has its own code path */
			column->typcat = TYPECAT_COMPOSITE_DOMAIN;
			column->io.composite.record_io = NULL;
			column->io.composite.tupdesc = NULL;
			column->io.composite.base_typid = base_typid;
			column->io.composite.base_typmod = base_typmod;
			column->io.composite.domain_info = NULL;
		}
		else
		{
			/* domain over anything else */
			column->typcat = TYPECAT_DOMAIN;
			column->io.domain.base_typid = base_typid;
			column->io.domain.base_typmod = base_typmod;
			column->io.domain.base_io =
				MemoryContextAllocZero(mcxt, sizeof(ColumnIOData));
			column->io.domain.domain_info = NULL;
		}
	}
	else if (type->typtype == TYPTYPE_COMPOSITE || typid == RECORDOID)
	{
		column->typcat = TYPECAT_COMPOSITE;
		column->io.composite.record_io = NULL;
		column->io.composite.tupdesc = NULL;
		column->io.composite.base_typid = typid;
		column->io.composite.base_typmod = typmod;
		column->io.composite.domain_info = NULL;
	}
	else if (type->typlen == -1 && OidIsValid(type->typelem))
	{
		column->typcat = TYPECAT_ARRAY;
		column->io.array.element_info = MemoryContextAllocZero(mcxt,
															   sizeof(ColumnIOData));
		column->io.array.element_type = type->typelem;
		/* array element typemod stored in attribute's typmod */
		column->io.array.element_typmod = typmod;
	}
	else
	{
		column->typcat = TYPECAT_SCALAR;
		need_scalar = true;
	}

	/* caller can force us to look up scalar_io info even for non-scalars */
	if (need_scalar)
	{
		Oid			typioproc;

		getTypeInputInfo(typid, &typioproc, &column->scalar_io.typioparam);
		fmgr_info_cxt(typioproc, &column->scalar_io.typiofunc, mcxt);
	}

	ReleaseSysCache(tup);
}