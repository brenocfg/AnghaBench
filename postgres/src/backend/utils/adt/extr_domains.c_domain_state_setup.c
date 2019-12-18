#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ typtype; int /*<<< orphan*/  domainBaseTypmod; int /*<<< orphan*/  domainBaseType; } ;
typedef  TYPE_1__ TypeCacheEntry ;
struct TYPE_6__ {int /*<<< orphan*/  domain_type; int /*<<< orphan*/  mcxt; int /*<<< orphan*/ * econtext; int /*<<< orphan*/  constraint_ref; int /*<<< orphan*/  proc; int /*<<< orphan*/  typiofunc; int /*<<< orphan*/  typioparam; int /*<<< orphan*/  typtypmod; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__ DomainIOData ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InitDomainConstraintRef (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TYPECACHE_DOMAIN_BASE_INFO ; 
 scalar_t__ TYPTYPE_DOMAIN ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmgr_info_cxt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getTypeBinaryInputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getTypeInputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* lookup_type_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DomainIOData *
domain_state_setup(Oid domainType, bool binary, MemoryContext mcxt)
{
	DomainIOData *my_extra;
	TypeCacheEntry *typentry;
	Oid			baseType;

	my_extra = (DomainIOData *) MemoryContextAlloc(mcxt, sizeof(DomainIOData));

	/*
	 * Verify that domainType represents a valid domain type.  We need to be
	 * careful here because domain_in and domain_recv can be called from SQL,
	 * possibly with incorrect arguments.  We use lookup_type_cache mainly
	 * because it will throw a clean user-facing error for a bad OID; but also
	 * it can cache the underlying base type info.
	 */
	typentry = lookup_type_cache(domainType, TYPECACHE_DOMAIN_BASE_INFO);
	if (typentry->typtype != TYPTYPE_DOMAIN)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("type %s is not a domain",
						format_type_be(domainType))));

	/* Find out the base type */
	baseType = typentry->domainBaseType;
	my_extra->typtypmod = typentry->domainBaseTypmod;

	/* Look up underlying I/O function */
	if (binary)
		getTypeBinaryInputInfo(baseType,
							   &my_extra->typiofunc,
							   &my_extra->typioparam);
	else
		getTypeInputInfo(baseType,
						 &my_extra->typiofunc,
						 &my_extra->typioparam);
	fmgr_info_cxt(my_extra->typiofunc, &my_extra->proc, mcxt);

	/* Look up constraints for domain */
	InitDomainConstraintRef(domainType, &my_extra->constraint_ref, mcxt, true);

	/* We don't make an ExprContext until needed */
	my_extra->econtext = NULL;
	my_extra->mcxt = mcxt;

	/* Mark cache valid */
	my_extra->domain_type = domainType;

	return my_extra;
}