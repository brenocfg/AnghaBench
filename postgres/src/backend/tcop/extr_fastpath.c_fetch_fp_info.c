#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fp_info {int /*<<< orphan*/  funcid; int /*<<< orphan*/  fname; int /*<<< orphan*/  argtypes; int /*<<< orphan*/  rettype; int /*<<< orphan*/  namespace; int /*<<< orphan*/  flinfo; } ;
struct TYPE_3__ {int /*<<< orphan*/  values; } ;
struct TYPE_4__ {int pronargs; int /*<<< orphan*/  proname; TYPE_1__ proargtypes; int /*<<< orphan*/  prorettype; int /*<<< orphan*/  pronamespace; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_proc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 int FUNC_MAX_ARGS ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  MemSet (struct fp_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmgr_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fetch_fp_info(Oid func_id, struct fp_info *fip)
{
	HeapTuple	func_htp;
	Form_pg_proc pp;

	Assert(OidIsValid(func_id));
	Assert(fip != NULL);

	/*
	 * Since the validity of this structure is determined by whether the
	 * funcid is OK, we clear the funcid here.  It must not be set to the
	 * correct value until we are about to return with a good struct fp_info,
	 * since we can be interrupted (i.e., with an ereport(ERROR, ...)) at any
	 * time.  [No longer really an issue since we don't save the struct
	 * fp_info across transactions anymore, but keep it anyway.]
	 */
	MemSet(fip, 0, sizeof(struct fp_info));
	fip->funcid = InvalidOid;

	fmgr_info(func_id, &fip->flinfo);

	func_htp = SearchSysCache1(PROCOID, ObjectIdGetDatum(func_id));
	if (!HeapTupleIsValid(func_htp))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION),
				 errmsg("function with OID %u does not exist", func_id)));
	pp = (Form_pg_proc) GETSTRUCT(func_htp);

	/* watch out for catalog entries with more than FUNC_MAX_ARGS args */
	if (pp->pronargs > FUNC_MAX_ARGS)
		elog(ERROR, "function %s has more than %d arguments",
			 NameStr(pp->proname), FUNC_MAX_ARGS);

	fip->namespace = pp->pronamespace;
	fip->rettype = pp->prorettype;
	memcpy(fip->argtypes, pp->proargtypes.values, pp->pronargs * sizeof(Oid));
	strlcpy(fip->fname, NameStr(pp->proname), NAMEDATALEN);

	ReleaseSysCache(func_htp);

	/*
	 * This must be last!
	 */
	fip->funcid = func_id;
}